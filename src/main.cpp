#include <iostream>

/*
Test RTSP reading based on: 
      https://programmer.help/blogs/use-ffmpeg-to-read-video-stream-and-save-it.html
*/

#ifndef INT64_C 
#define INT64_C(c) (c ## LL) 
#define UINT64_C(c) (c ## ULL) 
#endif

extern "C" {
/*Include ffmpeg header file*/
#include <libavformat/avformat.h> 
#include <libavcodec/avcodec.h> 
#include <libswscale/swscale.h> 

#include <libavutil/imgutils.h>  
#include <libavutil/opt.h>     
#include <libavutil/mathematics.h>   
#include <libavutil/samplefmt.h>
}


int main(int argc, char** ardv){

	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	const char* in_filename, * out_filename;
	in_filename = "rtsp://127.0.0.1:8080/test.sdp";
	out_filename = "output.flv";
	
    avformat_network_init();

    //Setup params
    AVDictionary* avdic = NULL;
	char* option_key = "rtsp_transport";  char* option_value = "tcp";
	av_dict_set(&avdic, option_key, option_value, 0);
	char* option_key2 = "max_delay";        char* option_value2 = "5000000";
	av_dict_set(&avdic, option_key2, option_value2, 0);
    AVPacket pkt;
	AVOutputFormat* ofmt = NULL;
	int video_index = -1;
	int frame_index = 0;
    int i;

    //Open the input stream
	int ret;
	if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, &avdic)) < 0){
		printf("Could not open input file.\n");
		goto end;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0){
		printf("Failed to retrieve input stream information\n");
		goto end;
	}
    //find video stream
	for (i = 0; i < ifmt_ctx->nb_streams; i++){ 
		if (ifmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
			//Video streaming
			video_index = i;
			printf("Got videostream index: %d\n",i);
			break;
		}
	}
    //print information about other streams
	av_dump_format(ifmt_ctx, 0, in_filename, 0);

    //trurn on out stream -  find the appropriate AVFormatContext management structure based on the file name. 
    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
	if (!ofmt_ctx){
		printf("Could not create output context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}
    //Write file header to output file
    ret = avformat_write_header(ofmt_ctx, NULL);
    if (ret < 0){
    	printf("Error occured when opening output URL\n");
    	goto end;
    }
   
    //Put data to file

    while (1){
		AVStream* in_stream, * out_stream;
		//Get a packet from the input stream
		ret = av_read_frame(ifmt_ctx, &pkt);//Read a frame and put it in pkt
		if (ret < 0){
            printf("Read failure\n");
			break;
        }

		in_stream = ifmt_ctx->streams[pkt.stream_index];
		out_stream = ofmt_ctx->streams[pkt.stream_index];
		//copy packet
		//Conversion of PTS/DTS Timing
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, 
            (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, 
            (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		//printf("pts %d dts %d base %d\n",pkt.pts,pkt.dts, in_stream->time_base);
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;

		//Not all packet s in this while loop are video frames. Record the video frames when they are received, that's all.
		if (pkt.stream_index == video_index){
			printf("Receive %8d video frames from input URL\n", frame_index);
			frame_index++;
		}
		//Write the package data to a file.
		ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
		if (ret < 0){
			if (ret == -22) {
				continue;
			} else {
				printf("Error muxing packet.error code %d\n", ret);
				break;
			}
		}
		av_packet_unref(&pkt);
	}


	//Write the end of the file
	av_write_trailer(ofmt_ctx);

end:
	av_dict_free(&avdic);
	avformat_close_input(&ifmt_ctx);
	//Close input
	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE)){
		avio_close(ofmt_ctx->pb);
    }
	avformat_free_context(ofmt_ctx);
	if (ret < 0 && ret != AVERROR_EOF){
		printf("Error occured.\n");
		return -1;
	}
	return 0;
}


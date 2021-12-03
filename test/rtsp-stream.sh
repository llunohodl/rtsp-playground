# load test mp4 file
if [ ! -f "./sample-mp4-file.mp4" ]; then
wget https://jsoncompare.org/LearningContainer/SampleFiles/Video/MP4/sample-mp4-file.mp4
fi
#stream test file as H264 encoded video to "rtsp://127.0.0.1:8080/test.sdp"
cvlc -vvv --repeat sample-mp4-file.mp4 \
--sout '#transcode{vcodec=h264,scale=Auto,width=320,height=240,acodec=none,scodec=none}:rtp{dst=192.168.0.12,port=1234,sdp=rtsp://127.0.0.1:8080/test.sdp}' \
--sout-keep
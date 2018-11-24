# coding=utf-8  
  
import os  
import cv2  
  
def video2frame(video_src_path, formats, frame_save_path, frame_width, frame_height, interval):  
    """  
    将视频按固定间隔读取写入图片  
    :param video_src_path: 视频存放路径  
    :param formats:　包含的所有视频格式  
    :param frame_save_path:　保存路径  
    :param frame_width:　保存帧宽  
    :param frame_height:　保存帧高  
    :param interval:　保存帧间隔  
    :return:　帧图片  
    """  
    videos = os.listdir(video_src_path)  
  
    def filter_format(x, all_formats):  
        if x[-4:] in all_formats:  
            return True  
        else:  
            return False  
  
    videos = filter(lambda x: filter_format(x, formats), videos)  
  
    for each_video in videos:  
        print("正在读取视频：", each_video)  
  
        each_video_name = each_video[:-4]  
        os.mkdir(frame_save_path + each_video_name)  
        each_video_save_full_path = os.path.join(frame_save_path, each_video_name) + "/"  
  
        each_video_full_path = os.path.join(video_src_path, each_video)  
  
        cap = cv2.VideoCapture(each_video_full_path)  
        frame_index = 0  
        frame_count = 0  
        if cap.isOpened():  
            success = True  
        else:  
            success = False  
            print("读取失败!")  
  
        while(success):  
            success, frame = cap.read()  
            print("---> 正在读取第%d帧:" % frame_index, success)
  
            if frame_index % interval == 0:  
                resize_frame = cv2.resize(frame, (frame_width, frame_height), interpolation=cv2.INTER_AREA)  
                # cv2.imwrite(each_video_save_full_path + each_video_name + "_%d.jpg" % frame_index, resize_frame)  
                cv2.imwrite(each_video_save_full_path + "%d.jpg" % frame_count, resize_frame)  
                frame_count += 1  
  
            frame_index += 1  
  
    cap.release()  
  
def frame2vedio(img_root, fps, size):
   # img_root = 'F:\\test\\'                     #这里写你的文件夹路径，比如：/home/youname/data/img/,注意最后一个文件夹要有斜杠
   # fps = 30                                    #保存视频的FPS，可以适当调整
   # size=(960,544)
    #可以用(*'DVIX')或(*'X264'),如果都不行先装ffmepg: sudo apt-get install ffmepg
    vedio_path = os.path.join(img_root, "3.avi")
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    videoWriter = cv2.VideoWriter(vedio_path, fourcc, fps, size)#最后一个是保存图片的尺寸

    #for(i=1;i<471;++i)
    for i in range(1,327):
        frame = cv2.imread(img_root+str(i)+'.jpg')
        videoWriter.write(frame)
    videoWriter.release()


if __name__ == '__main__':  
    videos_src_path ="E:\\cuiyue\\T_Git\\ContentQuery\\code\\src\\vedioFrame\\" 
    frames_src_path = videos_src_path + "005\\"
    video_formats = [".MP4", ".MOV"]  
    frames_save_path = "E:\\cuiyue\\T_Git\\ContentQuery\\code\\src\\vedioFrame\\"
    width = 320 
    height = 240  
    time_interval = 10
    size = (width, height)
   # video2frame(videos_src_path, video_formats, frames_save_path, width, height, time_interval)  
    frame2vedio(frames_src_path, 30, size)

#coding=utf-8
import sys
import os
import jieba
import importlib

importlib.reload(sys)
#分类语料库路径
corpus_path = "text_corpus_small"+"/"
#分词后的语料库路径
seg_path = "text_corpus_segment"+"/"

#get all subdirectories in corpus
dir_list = os.listdir(corpus_path)

#get all files in each subdirectory
for mydir in dir_list:
	class_path = corpus_path + mydir + "/"
	file_list = os.listdir(class_path)			#lsit all files under class_path
	for file_path in file_list:					#traverse all files
		file_name = class_path + file_path		#montage full file path
		file_read = open(file_name, 'rb')
		raw_corpus = file_read.read()			#read raw corpus
		seg_corpus = jieba.cut(raw_corpus)		#jieba split operation
		seg_corpus_str = " ".join(seg_corpus)
		
		#creat new dir for splited corpus
		seg_dir = seg_path + mydir + "/"
		if not os.path.exists(seg_dir):			#if failed
			os.makedirs(seg_dir)
		file_write = open(seg_dir + file_path,'wb')	#create splited files the same name with raw files
		file_write.write(seg_corpus_str.encode())	#use blank seperate the results and write them into splited files
		file_read.close()						#close file
		file_write.close()		

print("success to split the corpus")




















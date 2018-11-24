#encoding=utf-8
import jieba
import os,shutil
import random
import pickle	#permanant serialize
import numpy as np
import imp
import datetime
from sklearn import feature_extraction
from sklearn.feature_extraction.text import TfidfTransformer 	#TF-IDF vector transformation class
from sklearn.feature_extraction.text import TfidfVectorizer		#TF-IDF vector generalization class
from sklearn.datasets.base import Bunch
from sklearn.naive_bayes import MultinomialNB			#multinomial bayes algorithm

def readFile(path):
	with open(path,'r',errors='ignore') as file:	#filter problem in text with errors
		content = file.read()
		return content

def saveFile(path,result):
	with open(path,'w',errors='ignore') as file:	#filter problem in text with errors
		content = file.write(result)

def myPrint(content):
	strTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
	print(strTime+"->"+content)

def segCorpus(inputPath, resultPath):	
	myPrint("segCorpus")
	dir_list = os.listdir(inputPath)				#get all subdirectories in corpus
	for each_dir in dir_list:							#get all files in each subdirectory
		class_path = inputPath + each_dir + "/"
		file_list = os.listdir(class_path)			#lsit all files under class_path
		for each_file in file_list:					#traverse all files
			file_name = class_path + each_file		#montage full file path
			raw_corpus = readFile(file_name)			#read raw corpus
			seg_corpus = jieba.cut(raw_corpus)		#jieba split operation
			#seg_corpus_str = " ".join(seg_corpus)
			#creat new dir for splited corpus
			seg_dir = resultPath + each_dir + "/"
			if not os.path.exists(seg_dir):			#if failed
				os.makedirs(seg_dir)
			saveFile(seg_dir+each_file," ".join(seg_corpus))

def crossDvideSample(inputPath, outputPath):
	myPrint("generate test sets")
	dir_list = os.listdir(inputPath)
	for each_dir in dir_list:
		class_path = inputPath + each_dir + "/"
		file_list = os.listdir(class_path)
		count_test = int(len(file_list)/10)
		for count in range(count_test):
			file_list = os.listdir(class_path)
			file_move = file_list[random.randint(0,len(file_list)-1)]
			src = class_path + file_move
			dst_dir = outputPath + each_dir + "/"
			if not os.path.exists(dst_dir):
				os.makedirs(dst_dir)
			dst = dst_dir + file_move
			shutil.move(src,dst)

def bunchSave(inputFile,outputFile):
	myPrint("bunchSave")
	catelist = os.listdir(inputFile)
	bunch = Bunch(target_name=[],label=[],filenames=[],contents=[])
	bunch.target_name.extend(catelist)				#save class names into object Bunch
	for eachDir in catelist:
		eachPath = inputFile + eachDir + "/"
		fileList = os.listdir(eachPath)
		for eachFile in fileList:					#travers each file in the second subdir
			fullName = eachPath + eachFile			#whole file path of each file
			bunch.label.append(eachDir)				#current class
			bunch.filenames.append(fullName)		#save current file path
			bunch.contents.append(readFile(fullName).strip())	#save wordvector
	writeBunch(outputFile,bunch)

def readBunch(path):
	with open(path,'rb') as file:
		bunch = pickle.load(file)
	return bunch

def writeBunch(path,bunchFile):
	with open(path,'wb') as file:
		pickle.dump(bunchFile, file)

def getStopWord(inputFile):
	myPrint("getStopWord")
	stopWrodList = readFile(inputFile).splitlines()
	return stopWrodList

def getTFIDFMat(inputPath, stopWordList, outputPath):	#get TF-IDF vector
	myPrint("getTFIDFMat")
	bunch = readBunch(inputPath)
	tfidfspace = Bunch(target_name=bunch.target_name,label=bunch.label, filenames=bunch.filenames,tdm=[],vocabulary={})
	#initialize vector space
	vectorizer = TfidfVectorizer(stop_words=stopWordList, sublinear_tf=True,max_df=0.5)
	transfomer = TfidfTransformer()					#this could calculate weight of each worc
	#transform text into word frequnece matrix,then save the dicrionary only
	tfidfspace.tdm = vectorizer.fit_transform(bunch.contents)
	tfidfspace.vocabulary = vectorizer.vocabulary_	#get vocabulary
	writeBunch(outputPath, tfidfspace)

def getTestSpace(testSetPath,trainSpacePath,stopWordList,testSpacePath):
	myPrint("getTestSpace")
	bunch = readBunch(testSetPath)
	#get TF-IDF vector space of test set
	testSpace = Bunch(target_name=bunch.target_name, label=bunch.label,filenames=bunch.filenames,tdm=[],vocabulary={})
	#load trainset word bag
	trainbunch = readBunch(trainSpacePath)
	#initialize vector space model by TfidfVecorizer with train set word vector
	vectorizer = TfidfVectorizer(stop_words=stopWordList,sublinear_tf=True,max_df=0.5,vocabulary=trainbunch.vocabulary)
	transformer = TfidfTransformer()
	testSpace.tdm = vectorizer.fit_transform(bunch.contents)
	testSpace.vocabulary = trainbunch.vocabulary
	writeBunch(testSpacePath, testSpace)			#serialize

def bayesAlgorithm(trainPath, testPath):
	myPrint("bayesAlgorithm")
	trainSet = readBunch(trainPath)
	testSet = readBunch(testPath)
	clf = MultinomialNB(alpha=0.001).fit(trainSet.tdm,trainSet.label)
	print(np.shape(trainSet.tdm))
	print(np.shape(testSet.tdm))
	predicted = clf.predict(testSet.tdm)
	total = len(predicted)
	rate = 0
	for flabel,fileName,expct_cate in zip(testSet.label,testSet.filenames,predicted):
		if flabel != expct_cate:
			rate+=1
			print(fileName, ":real class:",flabel,"-->predicted class:", expct_cate)
	print("error rate:", float(rate)*100/float(total), "%")

#the entrance of this procedure
corpus_path = "./corpus/"
corpus_seg_path = corpus_path.rstrip("/")+"_seg/"
corpus_test_path = corpus_path.rstrip("/")+"_test/"
corpus_test_seg_path = corpus_test_path.rstrip("/")+"_seg/"
crossDvideSample(corpus_path, corpus_test_path)	#devide trainset and testset
segCorpus(corpus_path, corpus_seg_path)	#split samples by jieba and save in another dir
bunchSave(corpus_seg_path,"./train_set.dat")				#input word,output wordvector
stopWrodList = getStopWord("./stopwordCategory/commonStopwords.txt")	#get stopwords
getTFIDFMat("./train_set.dat", stopWrodList,"./tfidfspace.dat")	#input wordvector,output characteristic space

#test
segCorpus(corpus_test_path, corpus_test_seg_path)		#splilt test set
bunchSave(corpus_test_seg_path, "./test_set.dat")		#output test set wordvector
getTestSpace("./test_set.dat","./tfidfspace.dat",stopWrodList,"./testspace.dat")
bayesAlgorithm("./tfidfspace.dat","./testspace.dat")	#sklearn bayes classification















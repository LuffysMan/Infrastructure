@echo off
DEL/S/Q train_set.dat,test_set.dat,tfidfspace.dat,testspace.dat
RD/S/Q corpus,corpus_seg,corpus_test,corpus_test_seg
mkdir .\corpus
xcopy .\corpus_copy\*.* .\corpus /S



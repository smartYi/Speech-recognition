clear;
clc;

a = load('ZEpower.txt');
length = size(a,1);

b = reshape(a,length/13,13);

imagesc(b);


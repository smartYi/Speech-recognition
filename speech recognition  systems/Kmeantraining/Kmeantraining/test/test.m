clc;
clear;

load('s1.mat');
load('s2.mat');
load('s3.mat');
load('s4.mat');
load('s5.mat');

X1 = load('1.txt')';
X2 = load('2.txt')';
X3 = load('3.txt')';
X4 = load('4.txt')';
X5 = load('5.txt')';

mean1 = mean(s1)';
mean2 = mean(s2)';
mean3 = mean(s3)';
mean4 = mean(s4)';
mean5 = mean(s5)';

c1 = zeros(39);
c2 = zeros(39,1);
for i = 1 : size(s5,1)
    tem = s5(i,:)' - mean5;
    ckj = tem * tem';
    c1 = c1 + ckj;
end

c1 = c1 ./ size(s5,1);
count = 0;
for i = 1 : 39
    count = count + 1;
    c11(count) = c1(i,i);
end

c11 = c11';

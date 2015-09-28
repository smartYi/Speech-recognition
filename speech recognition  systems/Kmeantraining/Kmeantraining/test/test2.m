% 
% X1 = load('1.txt')';X2 = load('2.txt')';X3 = load('3.txt')';X4 = load('4.txt')';X5 = load('5.txt')';
% 
% load('c1.mat');load('c2.mat');load('c3.mat');load('c4.mat');load('c5.mat');
% 
% 
% 
% load('s1.mat');load('s2.mat');load('s3.mat');load('s4.mat');load('s5.mat');
% cd1 = diag(c1);cd2 = diag(c2);cd3 = diag(c3);cd4 = diag(c4);cd5 = diag(c5);
% mean1 = mean(s1)';mean2 = mean(s2)';mean3 = mean(s3)';mean4 = mean(s4)';mean5 = mean(s5)';
% 
% d = zeros(5,82);

for i = 1 : 82
    d1 = (X1(:,i) - mean5)' / cd5;
    d1 = d1 * (X1(:,i) - mean5);
    sita = 0;
    for j = 1 : 39
        sita = sita + log(2 * 3.1415 * c5(j));
    end
    sumd = 0.5 * (sita + d1);
    d(5,i) = sumd;
end
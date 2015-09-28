clear;
clc;
input = load('input_record.txt');
template = load('digit_number_9.txt');
cost = zeros(size(template,1),size(input,1));

for i = 1:size(template,1);
    for j =1:size(input,1);
      cost(i,j) = sqrt((template(i,:) - input(j,:))*(template(i,:) - input(j,:))');
    end
end
        
y = load('ZEpower.txt');
cept = zeros(13, size(y, 1) / 13);
count = 1;
for i = 1 : size(y, 1) / 13
    for j = 1 : 13
        cept(j, i) = y(count);
        count = count + 1;
    end
end
imagesc(cept);


[x,fs] = wavread('recorded.wav');
wlen = 200; inc = 80;
win = hanning(wlen);
N=length(x);
X=enframe(x,win,inc)';
fn=size(X,2);
time = (0:N-1)/fs;
for i=1:fn;
u=X(:,i);
u2 = u.*u;
En(i)= sum(u2);
end
subplot 211;
plot(time,x,'k');

frametime = frame2time(fn,wlen,inc,fs);
subplot 222;plot(frametime,En,'k');

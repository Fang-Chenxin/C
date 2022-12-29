close all;
clear;

filename1 = 'line.txt';
[x,y]=textread(filename1,'%n %n');


filename2 = 'Pt.txt';
[Px,Py]=textread(filename2,'%n %n');

figure(1);
title('BeizerCurve'); 
hold on;
plot(x,y,'b');
hold on;
scatter(Px,Py,'*','r');
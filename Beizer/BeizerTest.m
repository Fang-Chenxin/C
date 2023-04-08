close all;
clear;

filename1 = 'line.txt';
fileID1 = fopen(filename1);
xy=textscan(fileID1,'%n %n');
fclose(fileID1);


filename2 = 'Pt.txt';
fileID2 = fopen(filename2);
P=textscan(fileID2,'%n %n');
fclose(fileID2);

figure(1);
title('BeizerCurve'); 
hold on;
plot(xy{1},xy{2},'b');
hold on;
scatter(P{1},P{2},'*','r');
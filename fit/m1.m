clc;clear;close all;
data = readtable("data.xlsx",'Sheet',5,'VariableNamingRule','preserve');
cnt = data.paper;
% freq = data.freq;
mcu = data.mcu;
mcu1 = mcu(1:12) - 0.5;
mcu2 = mcu(13:end) - 1;
mcu_n = [mcu1; mcu2];
figure
% plot(cnt, mcu_n,LineWidth=1.5)
plot(cnt, mcu,LineWidth=1.5)
hold on
plot(cnt, cnt, LineStyle="--",LineWidth=1.5)
plot(cnt,cnt+1,LineStyle='--')
plot(cnt,cnt+2,LineStyle='--')
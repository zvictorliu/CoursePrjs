clc;clear;close all;
data = readtable("data.xlsx",'Sheet',9,'VariableNamingRule','preserve');
cnt = data.paper;
% freq = data.freq;
mcu = data.mcu;

% p = polyfit(cnt, freq, 1);
% y = polyval(p, cnt);
p0 = polyfit(mcu, cnt, 3);
y0 = polyval(p0, mcu);

% figure
% plot(cnt, freq,'LineWidth',1.5,'Marker','o')
% hold on
% plot(cnt, y, 'LineWidth',1.5,'LineStyle','--')
% plot(cnt, mcu,'LineWidth',1.5,'Marker','o')
% xlabel("纸张数量")
% ylabel("频率 (Hz)")
% legend("示波器","示波器拟合","单片机")

figure
plot(mcu, cnt,'LineWidth',1.5)
hold on
plot(mcu, y0+0.5, 'LineWidth',1.5,'LineStyle','--')
% plot(mcu, cnt+1,'LineStyle','--' , 'LineWidth',1)
% plot(mcu, cnt-1,'LineStyle','--' , 'LineWidth',1)
xlabel("频率Hz")
legend("原始","拟合")
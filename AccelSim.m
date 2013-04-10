kCFAbsoluteTimeIntervalSince1970 = 978307200.0;

u=udp('127.0.0.1', 10553);
fopen(u)

for i = 1:size(accelData,1)
    t = etime(clock,[1970 1 1 0 0 0]) - kCFAbsoluteTimeIntervalSince1970;
    tmp = sprintf('%s,%f,%f,%f,%f','ACC: 0',t, [accelData(i,:)])
    fwrite(u, tmp);
    
    pause(0.3);
end
fclose(u)

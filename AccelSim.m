kCFAbsoluteTimeIntervalSince1970 = 978307200.0;

u=udp('127.0.0.1', 10553);
fopen(u)

for i = 1:size(acc_ts,1)
    t = etime(clock,[1970 1 1 0 0 0]) - kCFAbsoluteTimeIntervalSince1970;
    tmp = sprintf('%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f','DEV: 0',t, [acc_ts(i,:)],[rotv_ts(i,:)],[att_ts(i,:)])
    fwrite(u, tmp);
    %%disp(tmp);
    pause(0.1);
end
fclose(u)

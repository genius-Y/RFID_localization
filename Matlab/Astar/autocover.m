clear, clc, clf
load('newmodel')
% model=newmodel;
map=zeros(size(model));
start=[2,2];
s=start;
path=s;
map(s(1,1),s(1,2))=-2;
move=1;
b=1;
while size(b,1)~=0
    move=1;
    while move==1 % s not a critical point
        map=pseudosense(s,model,map);
        [s,map,move] = Oxmove(s,map);
        path=[path ; s];
        if move==0
            scp=s;
            [b] = backtrack(path,map,scp);
        end
    end
    if size(b,1)==0
        break
    end
    path1 = Astar(b,scp,map);

    path = [path ; path1];
    s=path(length(path),:);
end

%%
% plot(start(1,1),start(1,2),'r*',path(:,1),path(:,2),'b-','Linewidth',6)

% hold on;
% plot(path1(:,1),path1(:,2),'r-','Linewidth',2)
figure(1)
surf(map)
figure(2)
clf(figure(2),'reset')
pause(2)
h=animatedline('Color','b','LineWidth',12);
for t=1:length(path)
    addpoints(h,path(t,1),path(t,2))
    drawnow
end

%%
figure
surf(map)
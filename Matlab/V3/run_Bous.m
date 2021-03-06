clear, clc, clf
load('model')
map=zeros(size(model));
start=[2,2];
s=start;
path=s;
map(s(1,1),s(1,2))=-2;
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
%%
[path1] = Astar(scp,b,map);

%%
plot(path(:,1),path(:,2),'b-','Linewidth',9)
hold on
plot(start(1,1),start(1,2),'go',path(541,1),path(541,2),'ro','Linewidth',9)
legend('Path','Start','Critical Point')
axis tight
%%
% hold on;
% plot(path1(:,1),path1(:,2),'r-','Linewidth',2)
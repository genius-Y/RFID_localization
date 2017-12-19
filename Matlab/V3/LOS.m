function [los] = LOS(s0,s1,map)
% Checks for LOS for points s0 and s1 in the map and returns 
    x0=s0(1,1);
    y0=s0(1,2);
    x1=s1(1,1);
    y1=s1(1,2);
    dy=y1-y0;
    dx=x1-x0;
    f=0;
    if dy<0
        dy=-dy;
        sy=-1;
    else
        sy=1;
    end
    if dx<0
        dx=-dx;
        sx=-1;
    else
        sx=1;
    end
    if dx>=dy
        while x0~=x1
            f=f+dy;
            if f>=dx
                if map(x0+((sx-1)/2),y0+((sy-1)/2))==-1
                    los=false;
                    return
                end
                y0=y0+sy;
                f=f-dx;
            end
            if f~=0 && map(x0+((sx-1)/2),y0+((sy-1)/2))==-1
                los=false;
                return
            end
            if dy==0 && map(x0+((sx-1)/2),y0)==-1 %&& map(x0+((sx-1)/2),y0-1)==-1
                los=false;
                return
            end
            x0=x0+sx;
        end
    else
        while y0~=y1
            f=f+dx;
            if f>=dy
                if map(x0+((sx-1)/2),y0+((sy-1)/2))==-1
                    los=false;
                    return
                end
                x0=x0+sx;
                f=f-dy;
            end
            if f~=0 && map(x0+((sx-1)/2),y0+((sy-1)/2))==-1
                los=false;
                return
            end
            if dx==0 && map(x0,y0+((sy-1)/2))==-1 %&& map(x0-1,y0+((sy-1)/2))==-1
                los=false;
                return
            end
            y0=y0+sy;
        end
    end
    los=true;
    return
end


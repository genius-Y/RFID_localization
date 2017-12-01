%% Part a
close, clear, clc
v=randn([1,3000]);
w=randn([1,3000]);
x=linspace(-3,3,3000);
v1=1/sqrt(2*pi)*exp(-x.^2/2); % ????????
histogram(v,50)
figure;
histogram(v1,50) % :|
mean_v=mean(v), var_v=var(v)
%% Part b

close, clear, clc
time=linspace(0,3000,3001);
v = randn([1,3001]);
w = randn([1,3001]);
u = zeros(1,length(time));
x(:,1) = [0 0]';
A = [ 0.3  0.5
     -0.2  1.0];
B = [0 1]'; C = [1 0]; G = [0 1]';

for t=1:length(time)
    
    x(:,t + 1) = A*x(:,t) + B*u(t) + G*v(t);
    y(:,t) = C*x(:,t) + w(t);
end
histogram(y,50)
hold on
histogram(v,50)
legend('y','v')
mean_v=mean(v), var_v=var(v), mean_y=mean(y), var_y=var(y)
 
%% Part c and d

close, clear, clc
time=linspace(0,3000,3001);
v = randn([1,3001]);
w = randn([1,3001]);
u = zeros(1,length(time)); uhat=u;
x(:,1) = [0 0]'; xhat(:,1)=x(:,1);
A = [ 0.3  0.5
     -0.2  1.0];
B = [0 1]'; C = [1 0]; G = [0 1]';
L1 = [0.01, 0.01]' ; L2 = [0.4 0.4]'; L3 = [1.2 1.8]';
for L=[L1,L2,L3]
for t=1:length(time)
    
    x(:,t + 1) = A*x(:,t) + B*u(t) + G*v(t);
    y(:,t) = C*x(:,t) +w(t);
    xhat(:,t + 1) = A*xhat(:,t) + B*uhat(:,t) + L*(y(:,t) - C*xhat(:,t));
end
b=0;
for i=1:length(x)
    a=(x(:,i)-xhat(:,i)).^2;
    b=b+a;
end
mse= 1/(length(x))*(b)
end
%% part e
clc
for L=[L1,L2,L3]
eigen=eig(A-L*C)
end

%% Part f

close, clear, clc
time=linspace(0,3000,3001);
v = randn([1,3001]);
w = zeros([1,3001]);
u = zeros(1,length(time)); uhat=u;
x(:,1) = [0 0]'; xhat(:,1)=x(:,1);
A = [ 0.3  0.5
     -0.2  1.0];
B = [0 1]'; C = [1 0]; G = [0 1]';
L1 = [0.01, 0.01]' ; L2 = [0.4 0.4]'; L3 = [1.2 1.8]';
for L=[L1,L2,L3]
for t=1:length(time)
    
    x(:,t + 1) = A*x(:,t) + B*u(t) + G*v(t);
    y(:,t) = C*x(:,t) +w(t);
    xhat(:,t + 1) = A*xhat(:,t) + B*uhat(:,t) + L*(y(:,t) - C*xhat(:,t));
end
b=0;
for i=1:length(x)
    a=(x(:,i)-xhat(:,i)).^2;
    b=b+a;
end
mse= 1/(length(x))*(b)
eigen=eig(A-L*C)
end

%% Part g


close, clear, clc
time=linspace(0,3000,3001);
v = zeros([1,3001]);
w = randn([1,3001]);
u = zeros(1,length(time)); uhat=u;
x(:,1) = [0 0]'; xhat(:,1)=x(:,1);
A = [ 0.3  0.5
     -0.2  1.0];
B = [0 1]'; C = [1 0]; G = [0 1]';
L1 = [0.01, 0.01]' ; L2 = [0.4 0.4]'; L3 = [1.2 1.8]';
for L=[L1,L2,L3]
for t=1:length(time)
    
    x(:,t + 1) = A*x(:,t) + B*u(t) + G*v(t);
    y(:,t) = C*x(:,t) +w(t);
    xhat(:,t + 1) = A*xhat(:,t) + B*uhat(:,t) + L*(y(:,t) - C*xhat(:,t));
end
b=0;
for i=1:length(x)
    a=(x(:,i)-xhat(:,i)).^2;
    b=b+a;
end
mse= 1/(length(x))*(b)
eigen=eig(A-L*C)
end
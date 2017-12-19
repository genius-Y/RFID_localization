from extendedKalmanFilter import ekf
import scipy.io as sio
mat = sio.loadmat('4style.mat')
straight=mat['straight']

for x in range(0,300):
	ekf.predict()
	ekf.update(straight[x,1:7])
	print 'i', x

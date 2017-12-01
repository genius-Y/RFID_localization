import numpy as np
import matplotlib.pyplot as plt

class FusionEKF:
    
    def __init__(self, sigma):
        self.x = np.array([0.,  #x
                           0.,  #y
                           0.,  #x_velocity
                           0.,  #y_velocity
                           0.,	#x_acceleration
                           0.,	#y_acceleration
                           0.,	#theta
                           0.,]).reshape(-1, 1) # omega
        self.i =	np.array([[0.],[0.]])
        self.p = np.diag([999 for i in iter(range(8))])
        self.sigma =  np.array([0.,  #sigma_x							#define sigma
								0.,  #sigma_y
								0.,  #sigma_x_velocity
								0.,  #sigma_y_velocity
								0.,	#sigma_x_acceleration
								0.,	#sigma_y_acceleration
								0.,	#sigma_theta
								0., #sigma_omega
								0., #sigma_vl
								0.,]).reshape(-1, 1) #sigma_vr
        
        self.q = q
        self.m = m		
        						
    def get_state_transition_matrix(self):								#MATRIX A
        x, y, dx, dy, ddx, ddy, th, dth= self.x
        vl, vr = self.i
        phi=th+0.5*dth*dt
        return np.array([[  1, 0, dt,  0, dt**2/2,       0,                              0,                             0],
						 [  0, 1,  0, dt,       0, dt**2/2,                              0,                             0],
						 [  0, 0,  0,  0,      dt,       0,         -np.sin(th)*(vl/2 + vr/2), -(dt*np.sin(th)*(vl/2 + vr/2))/2],
					  	 [  0, 0,  0,  0,       0,      dt,          np.cos(th)*(vl/2 + vr/2),  (dt*np.cos(th)*(vl/2 + vr/2))/2],
					 	 [  0, 0,  0,  0,       1,       0,                              0,                             0],
						 [  0, 0,  0,  0,       0,       1,                              0,                             0],
						 [  0, 0,  0,  0,       0,       0,                              1,                             dt],
						 [  0, 0,  0,  0,       0,       0,                              0,                             0]])

    def get_input_transition_matrix(self):								#MATRIX V
        x, y, dx, dy, ddx, ddy, th, dth= self.x
        phi=th+0.5*dth*dt
        return np.array([[		0,         0],
						[		0,         0],
						[np.cos(th)/2, np.cos(th)/2],
						[np.sin(th)/2, np.sin(th)/2],
						[		0,         0],
						[		0,         0],
						[		0,         0],
						[	 -1/d,       1/d]])

    def get_measurement_matrix(self):									#MATRIX ZHAT
        x, y, dx, dy, ddx, ddy, th, dth= self.x
        phi=th+0.5*dth*dt
        return np.array([[x,   0,   0,   0,   0,           0,           0,   0],
						[0,    y,   0,  0,   0,           0,           0,   0],
						[0,    0,   0,   0,   ddx*np.cos(phi),    ddy*np.sin(phi),    0,   0],
						[0,    0,   0,   0,   -ddx*np.sin(phi),   ddy*np.cos(phi),    0,   0],
						[0,    0,   0,   0,   0,           0,           th,   0],
						[0,    0,   0,   0,   0,           0,           0,   dth]])
        
    def get_measurement_jacobian(self):									#MATRIX H
        x, y, dx, dy, ddx, ddy, th, dth= self.x
        phi=th+0.5*dth*dt
        return np.array([[1, 0, 0, 0,         0,        0,                             0, 0],
						[0, 1, 0, 0,         0,        0,                             0, 0],
						[0, 0, 0, 0,  np.cos(phi), np.sin(phi),   ddy*np.cos(phi) - ddx*np.sin(phi), 0],
						[0, 0, 0, 0, -np.sin(phi), np.cos(phi), - ddx*np.cos(phi) - ddy*np.sin(phi), 0],
						[0, 0, 0, 0,         0,        0,                             1, 0],
						[0, 0, 0, 0,         0,        0,                             0, 1]])
						
    def predict(self,m,q):
        f = self.get_state_transition_matrix()
        v = self.get_input_transition_matrix()
        x, y, dx, dy, ddx, ddy, th, dth= self.x
        vl, vr = self.i
        new_x 	= x + dx*dt + ddx*dt^2/2								#xi_prio MATRIX
        new_y	= y + dy*dt + ddy*dt^2/2
        new_dx	= (vl+vr)/2*np.cos(th)+ddx*dt
        new_dy	= (vl+vr)/2*np.sin(th)+ddy*dt
        new_ddx	= ddx
        new_ddy	= ddy
        new_th	= th + dth*dt
        new_dth	= (vr-vl)/d
        sigx,sigy,sigdx,sigdy,sigddx,sigddy,sigth,sigdth,sigvl,sigvr=self.sigma
        q=np.diag([sigx[0],sigy[0],sigdx[0],sigdy[0],sigddx[0],sigddy[0],sigth[0],sigdth[0]])  #[0] hack to convert array to floats
        n=np.diag([sigvl[0],sigvr[0]])
        self.x = np.array([new_x, new_y, new_dx, new_dy, new_ddx, new_ddy, new_th, new_dth]).reshape(-1, 1)
        self.p = f.dot(self.p).dot(f.transpose()) + q + v.dot(self.m).dot(v.transpose())


    def update(self, measurement):
        z = np.array(measurement).reshape(-1, 1)						#Update states and covariance matrix
        zhat = get_measurement_matrix()
        h = get_measurement_jacobian()
        y = z - zhat

        s = self.h.dot(self.p).dot(self.h.transpose()) + self.r
        k = self.p.dot(self.h.transpose()).dot(np.linalg.inv(s))

        self.x = self.x + k.dot(y)
        self.p = (np.eye(8) - k.dot(self.h)).dot(self.p)

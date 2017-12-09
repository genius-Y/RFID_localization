import numpy as np

d = .24

class FusionEKF(object):

    def __init__(self, dt):
        self.dt = dt
        self.x = np.array([0., # x
                           0., # y
                           0., # x_velocity
                           0., # y_velocity
                           0., # x_acceleration
                           0., # y_acceleration
                           0., # theta
                           0., # omega
                           ]).reshape(-1, 1)
        self.i =    np.array([[0.3],[0.3]]) 							#figure out how to pass this to predict and update
        self.p = np.diag([999 for i in range(8)])
        self.sigma =  np.array([0., # sigma_x, define sigma
                                0., # sigma_y
                                0., # sigma_x_velocity
                                0., # sigma_y_velocity
                                0., # sigma_x_acceleration
                                0., # sigma_y_acceleration
                                0., # sigma_theta
                                0., # sigma_omega
                                0., # sigma_vl
                                0., # sigma_vr
                                ]).reshape(-1, 1)

        self.r = np.diag([0.79,0.30, 1.152e-05, 9.858e-05, 0.00000163, 3.6654e-06])
        self.q = 0.000001*np.eye(8)
        self.m = 0.000001*np.eye(2)

    def get_state_transition_matrix(self): # MATRIX A
        dt = self.dt
        x, y, dx, dy, ddx, ddy, th, dth= map(float,self.x)
        vr, vl = map(float,self.i)
        phi = float(th + 0.5*dth*dt)
        return np.array([[  1, 0, dt,  0, dt**2/2,       0,                              0,                             0],
                         [  0, 1,  0, dt,       0, dt**2/2,                              0,                             0],
                         [  0, 0,  0,  0,      dt,       0,         -np.sin(phi)*(vl/2 + vr/2), -(dt*np.sin(phi)*(vl/2 + vr/2))/2],
                         [  0, 0,  0,  0,       0,      dt,          np.cos(phi)*(vl/2 + vr/2),  (dt*np.cos(phi)*(vl/2 + vr/2))/2],
                         [  0, 0,  0,  0,       1,       0,                              0,                             0],
                         [  0, 0,  0,  0,       0,       1,                              0,                             0],
                         [  0, 0,  0,  0,       0,       0,                              1,                             dt],
                         [  0, 0,  0,  0,       0,       0,                              0,                             0]])

    def get_input_transition_matrix(self): # MATRIX V
        dt = self.dt
        x, y, dx, dy, ddx, ddy, th, dth= map(float,self.x)
        phi = float(th+0.5*dth*dt)
        return np.array([[      0,         0],
                        [       0,         0],
                        [np.cos(phi)/2, np.cos(phi)/2],
                        [np.sin(phi)/2, np.sin(phi)/2],
                        [       0,         0],
                        [       0,         0],
                        [       0,         0],
                        [    -1/d,       1/d]])

    def get_measurement_matrix(self): # MATRIX ZHAT
        x, y, dx, dy, ddx, ddy, th, dth= map(float,self.x)
        phi = float(th+0.5*dth*self.dt)
        return np.array([[1,   0,   0,   0,   0,           0,           0,   0],
                        [0,    1,   0,  0,   0,           0,           0,   0],
                        [0,    0,   0,   0,   np.cos(phi),   np.sin(phi),    0,   0],
                        [0,    0,   0,   0,   -np.sin(phi),   np.cos(phi),    0,   0],
                        [0,    0,   0,   0,   0,           0,           1,   0],
                        [0,    0,   0,   0,   0,           0,           0,   1]])

    def get_measurement_jacobian(self): # MATRIX H
        x, y, dx, dy, ddx, ddy, th, dth= map(float,self.x)
        phi = float(th+0.5*dth*self.dt)
        return np.array([[1, 0, 0, 0,         0,        0,                             0, 0],
                        [0, 1, 0, 0,         0,        0,                             0, 0],
                        [0, 0, 0, 0,  np.cos(phi), np.sin(phi),   ddy*np.cos(phi) - ddx*np.sin(phi), 0],
                        [0, 0, 0, 0, -np.sin(phi), np.cos(phi), - ddx*np.cos(phi) - ddy*np.sin(phi), 0],
                        [0, 0, 0, 0,         0,        0,                             1, 0],
                        [0, 0, 0, 0,         0,        0,                             0, 1]])

    def predict(self):
        f = self.get_state_transition_matrix()
        v = self.get_input_transition_matrix()
        dt = self.dt
        print 'x1', self.x
        print 'p1', self.p
        x, y, dx, dy, ddx, ddy, th, dth= map(float,self.x)
        vr, vl = map(float,self.i)
        new_x   = x + dx*dt + ddx*dt**2/2 # xi_prio MATRIX
        new_y   = y + dy*dt + ddy*dt**2/2
        new_dx  = (vl+vr)/2*np.cos(th)+ddx*dt
        new_dy  = (vl+vr)/2*np.sin(th)+ddy*dt
        new_ddx = ddx
        new_ddy = ddy
        new_th  = th + dth*dt
        new_dth = (vr-vl)/d
        #~ sigx,sigy,sigdx,sigdy,sigddx,sigddy,sigth,sigdth,sigvl,sigvr=self.sigma
        #~ q=np.diag([sigx[0],sigy[0],sigdx[0],sigdy[0],sigddx[0],sigddy[0],sigth[0],sigdth[0]]) #[0] hack to convert array to floats
        #~ q = np.diag(map(lambda x: x[0], self.sigma[:-2]))
        #~ n=np.diag([sigvl[0],sigvr[0]])
        #~ n = np.diag(map(lambda x: x[0], self.sigma[-2:]))
        self.xn = np.array([new_x, new_y, new_dx, new_dy, new_ddx, new_ddy, new_th, new_dth]).reshape(-1, 1)
        print 'x2', self.xn
        #~ print 'xn', self.xn
        self.pn = f.dot(self.p).dot(f.transpose()) + self.q + v.dot(self.m).dot(v.transpose())
        print 'p2', self.pn
        

    def update(self, *measurement):
        """ Update states and covariance matrix """
        dt = self.dt
        z = np.array(measurement).reshape(-1, 1)
        zhat = self.get_measurement_matrix()
        self.h = self.get_measurement_jacobian()
        y = z - zhat.dot(self.xn)
        s = self.h.dot(self.pn).dot(self.h.transpose()) + self.r
        
        #~ try:
        k = self.pn.dot(self.h.transpose()).dot(np.linalg.inv(s))
        #~ except np.LinAlgError:
            #~ k = np.zeros(8,6)
        print 'k', k
        self.x = self.xn + k.dot(y)
        print 'z', z
        print 'x3', self.x
        self.p = (np.eye(8) - k.dot(self.h)).dot(self.pn)
        print 'p3', self.p

ekf = FusionEKF(dt=0.02)

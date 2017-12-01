#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  sensor_fusion.py
#  
#  Copyright 2017 Nishant <Nishant@NISHANT>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  


from numpy import array, asarray
from numpy.random import randn
from filterpy.kalman import KalmanFilter
import matplotlib.pyplot as plt
import numpy as np
import book_plots as bp
import numpy.random as random

def fusion_test(wheel_sigma, ps_sigma, do_plot=True):
    dt = 0.1
    kf = KalmanFilter(dim_x=2, dim_z=2)

    kf.F = array([[1., dt], [0., 1.]])
    kf.H = array([[1., 0.], [1., 0.]])
    kf.x = array([[0.], [1.]])
    kf.Q *= array([[(dt**3)/3, (dt**2)/2],
                   [(dt**2)/2,  dt      ]]) * 0.02
    kf.P *= 100
    kf.R[0, 0] = wheel_sigma**2
    kf.R[1, 1] = ps_sigma**2 

    random.seed(1123)
    xs, zs, nom = [], [], []
    for i in range(1, 100):
        m0 = i + randn()*wheel_sigma
        m1 = i + randn()*ps_sigma
        z = array([[m0], [m1]])

        kf.predict()
        kf.update(z)

        xs.append(kf.x.T[0])
        zs.append(z.T[0])
        nom.append(i)

    xs = array(xs)
    zs = array(zs)
    nom = array(nom)
    
    res = nom - xs[:, 0]
    #print('fusion std: {:.3f}'.format(np.std(res)))
    
    ts = np.arange(0.1, 10, .1)
    bp.plot_measurements(ts, zs[:, 0], label='Wheel')
    plt.plot(ts, zs[:, 1], ls='--', label='Pos Sensor')
    bp.plot_filter(ts, xs[:, 0], label='Kalman filter')
    plt.legend(loc=4)
    plt.ylim(0, 100)
    bp.set_labels(x='time (sec)', y='meters')
    plt.show()
fusion_test(1.5, 3.0)

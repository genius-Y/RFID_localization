#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  intuition.py
#  
#  Copyright 2017 nishant <nishant@p500>
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

import numpy as np
from numpy.random import randn
import matplotlib.pyplot as plt

N = 3000
a = np.pi/2. + (randn(N) * 0.35)
r = 50.0     + (randn(N) * 0.4)
xs = r * np.cos(a)
ys = r * np.sin(a)

plt.figure()
plt.scatter(xs, ys, label='Sensor', color='k', marker='.', s=2)
xs, ys = sum(xs)/N, sum(ys)/N
plt.scatter(xs, ys, c='r', marker='*', s=200, label='Mean')
plt.scatter(0, 50, c='k', marker='o', s=300, label='Intuition')
plt.axis('equal')
plt.legend()
plt.show()

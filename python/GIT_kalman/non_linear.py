#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  non_linear.py
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
from numpy.random import randn , normal
import matplotlib.pyplot as plt

gaussian = (0., 1.)
data = normal(loc=gaussian[0], scale=gaussian[1], size=500000)
plt.figure()
plt.hist(2*data + 1, 1000);
plt.show()
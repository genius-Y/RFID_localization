Velocity-based dynamic model and adaptive controller for differential steered mobile robot
------
Blocks for simulation of the differential steered dynamics. Some controllers are included.
Available at: 
http://www.mathworks.com/matlabcentral/fileexchange/44850-velocity-based-dynamic-model-and-adaptive-controller-for-differential-steered-mobile-robot
---

These files allow the simulation of a differential steered (unicycle-like) mobile robot considering its complete dynamic model. The dynamic model here adopted is based on velocities (not torques), which makes it easier to integrate with existing mobile robot controllers that generate references for linear and angular velocities.

Although not required, the blocks were built to be compatible with Peter Corke's Robotics Toolbox, so the user can make use of the toolbox functions.

Sets of dynamic parameters are available for the following robots (obtained via identification):

- Pioneer 3-DX with Sick LASER sensor;
- Pioneer 3-DX without LASER sensor;
- Pioneer 2 without on-board computer (no LASER sensor);
- Pioneer 2 with on-board computer (no LASER sensor);
- Robotic wheelchair carrying a 55kg person;
- Robotic wheelchair carrying a 125kg person;
- Khepera III (LAUT, 2011);
- RobuLAB-10 (SHOJAEI et al., 2011).

The files include two libraries:

- "DiffSteer_model.slx": Library that contains the kinematic and dynamic blocks of the differential-drive mobile robot.

- "Controllers.slx": Library that contains the following blocks:
    a) trajectory tracking kinematic controller;
    b) dynamic compensation controller 1;
    c) dynamic compensation controller 2;
    d) dynamic parameters estimator (for adaptive controllers);
    e) trajectory generator;
    f) performance calculator (IAE, ITAE, ISE, ITSE and energy indexes).
If you are using Peter Corke's Robotics Toolbox, you might want to copy all files, specially "DiffSteer_model.slx" and "Controllers.slx" to the "...\rvctools\simulink" folder. 

Four Simulink systems are provided as examples:

1. "kinematic_controller_system.slx": implements a simple trajectory tracking controller using both kinematic and dynamic blocks of the differential drive mobile robot.

2. "dynamic_controller_system.slx": implements a more complex system that includes an adaptive dynamic compensation controller and the trajectory tracking controller. The system also has Band-Limited White Noise blocks to add some noise to the measured values of linear velocity, angular velocity and robot position (x,y).

Note: After running "kinematic_controller_system.slx" or "dynamic_controller_system.slx" simulations you can check the results calling the script "plot_results.m".

3. "sl_lanechange_unicycle.slx": implements the same system as the Robotics Toolbox "sl_lanechange", but using the kinematic model of the differential steered mobile robot.

4. "sl_lanechange_unicycle_dynamics.slx": implements the same system as the Robotics Toolbox "sl_lanechange", but using the kinematic and the dynamic models of the differential steered mobile robot.


Also, the following scripts are provided:

1. "sim_kin_controller.m": uses the "kinematic_controller_system.slx" system to simulate a kinematic trajectory tracking controller acting on a mobile robot (complete model).

2. "sim_dyn_controller.m": uses the "dynamic_controller_system.slx" system to simulate an adaptive dynamic compensation controller operating with the trajectory tracking controller acting on a mobile robot (complete model).

The scrpts "plot_results.m" and "plot_results_kin.m" present the results of the simulations.

All blocks were tested in MATLAB R2012b and R2013a running on Windows 7, and in MATLAB R2014b running on Windows 8.1. 


Enjoy!

Author: Felipe Nascimento Martins
Federal Institute of Education, Science and Technology of Espirito Santo - IFES
NERA - Núcleo de Estudos em Robótica e Automação
http://nera.sr.ifes.edu.br
MAY/2013
Blog sobre robótica: www.nossosrobos.blogspot.com

Based on a prior work by Felipe Nascimento Martins and Wanderley Cardoso Celeste
UFES - Federal University of Espirito Santo, BRAZIL
2006--2008

For detailed information on the system, please refer to the following papers and thesis:

MARTINS, F. N., Celeste, W. C., Carelli, R., Sarcinelli-Filho, M. and 
Bastos-Filho, T. F. An Adaptive Dynamic Controller for Autonomous Mobile Robot
Trajectory Tracking. Control Engineering Practice, v. 16, p. 1354–1363, 2008.
doi: 10.1016/j.conengprac.2008.03.004

MARTINS, F. N. Modelagem e Compensacao da Dinamica de Robos Moveis e sua 
Aplicacao em Controle de Formacao. Tese de Doutorado em Engenharia Eletrica - Automacao.
Universidade Federal do Espírito Santo, 2009.

LAUT, Jeffrey. A Dynamic Parameter Identification Method for Migrating Control Strategies 
Between Heterogeneous Wheeled Mobile Robots. M.Sc. Diss. Worcester Polytechnic Institute, 2011.

SHOJAEI, Khoshnam et al. Adaptive trajectory tracking control of a differential drive wheeled mobile robot. Robotica, v. 29, n. 03, p. 391-402, 2011.
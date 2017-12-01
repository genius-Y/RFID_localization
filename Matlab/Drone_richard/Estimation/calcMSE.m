run model_script
sim model_kf
close all;

kf_x = immse(x(:,2),x(:,3))
kf_y = immse(y(:,2),y(:,3))
kf_z = immse(z(:,2),z(:,3))
kf_phi = immse(phi(:,2),phi(:,3))
kf_theta= immse(theta(:,2),theta(:,3))
kf_psi = immse(psi(:,2),psi(:,3))
kf_u = immse(u(:,2),u(:,3))
kf_v = immse(v(:,2),v(:,3))
kf_w = immse(w(:,2),w(:,3))
kf_p = immse(p(:,2),p(:,3))
kf_q = immse(q(:,2),q(:,3))
kf_r = immse(r(:,2),r(:,3))

sim model_ekf
ekf_x = immse(x(:,2),x(:,3))
ekf_y = immse(y(:,2),y(:,3))
ekf_z = immse(z(:,2),z(:,3))
ekf_phi = immse(phi(:,2),phi(:,3))
ekf_theta= immse(theta(:,2),theta(:,3))
ekf_psi = immse(psi(:,2),psi(:,3))
ekf_u = immse(u(:,2),u(:,3))
ekf_v = immse(v(:,2),v(:,3))
ekf_w = immse(w(:,2),w(:,3))
ekf_p = immse(p(:,2),p(:,3))
ekf_q = immse(q(:,2),q(:,3))
ekf_r = immse(r(:,2),r(:,3))

sim model_ss_kf
f_x = immse(x(:,2),x(:,3))
f_y = immse(y(:,2),y(:,3))
f_z = immse(z(:,2),z(:,3))
f_phi = immse(phi(:,2),phi(:,3))
f_theta= immse(theta(:,2),theta(:,3))
f_psi = immse(psi(:,2),psi(:,3))
f_u = immse(u(:,2),u(:,3))
f_v = immse(v(:,2),v(:,3))
f_w = immse(w(:,2),w(:,3))
f_p = immse(p(:,2),p(:,3))
f_q = immse(q(:,2),q(:,3))
f_r = immse(r(:,2),r(:,3))

clearvars -except kf_x kf_y kf_z kf_phi kf_theta kf_psi kf_u kf_v kf_w kf_p kf_q kf_r...
    ekf_x ekf_y ekf_z ekf_phi ekf_theta ekf_psi ekf_u ekf_v ekf_w ekf_p ekf_q ekf_r...
    f_x f_y f_z f_phi f_theta f_psi f_u f_v f_w f_p f_q f_r
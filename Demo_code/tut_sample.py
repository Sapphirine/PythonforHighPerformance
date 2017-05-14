from math import sqrt

node_x = 1.0
node_y = 2.0
node_z = 2.0

node_vx = 0.0
node_vy = 0.5
node_vz = 0.0

node_m = 1

def single_step(node_x,node_y, node_z, dt):
    node_x = node_x
    node_y = node_y
    node_z = node_z
    # Compute force: gravity towards origin
    distance = sqrt(node_x**2 + node_y**2 + node_z**2)
    Fx = -node_x / distance**3
    Fy = -node_y / distance**3
    Fz = -node_z / distance**3
    # Time step position, according to velocity
    node_vx = 0.0
    node_vy = 0.5
    node_vz = 0.0
    node_x += dt * node_vx
    node_y += dt * node_vy
    node_z += dt * node_vz
    # Time step velocity, according to force and mass
    node_vx += dt * Fx / node_m
    node_vy += dt * Fy / node_m
    node_vz += dt * Fz / node_m

def step_time(node_x,node_y, node_z, time_span, n_steps):
    dt = time_span/n_steps
    for j in range(n_steps):
        single_step(node_x,node_y, node_z, dt)

step_time(node_x,node_y, node_z,0.00001,400000)

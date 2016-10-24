function [  ] = frame_beams( data_path,verbose )
%
%        | 10kN
%        |
%        \/      _
%        /\     |1.5 m
%       /  \    |_
%      |    |   | 2m
%      |    |   |_
%     ///  ///
%      <-><->
%      1m  1m
% 4 beams

%% defining the structure
% nodes
p1 = [0  , 0  , 0];
p2 = [0  , 1  , 0];
p3 = [0  , 2  , 0];
p4 = [0.5, 2.75,0];
p5 = [1  , 3.5 ,0];
p6 = [1.5, 2.75,0];
p7 = [2  , 2   ,0];
p8 = [2  , 1   ,0];
p9 = [2  , 0   ,0];

% topology of the structure
beam_start_pt = [ p1; p2; p3; p4; p5; p6; p7; p8 ];
beam_end_pt   = [ p2; p3; p4; p5; p6; p7; p8; p9 ];

% structural properties of the beams
E = 1;
A = 2300E-6; % in m^2
Iy = 1;% 1.2;  % TODO: need to find real values
Iz = 1;% 1.3;  % TODO: need to find real values
Iyz = 0;% 1.4; % TODO: need to find real values
GJ = 0;% 1.5;    % TODO: need to find real values
alpha = 0; % in degrees

% the structure is not cyclic
cyclic = 0;

% external force applied on the structure
fext = [2,6,-10E3]; % force at point 6, along the direction Y, amplitude: -10E3

% supports and constraints
% constraints everything at point 1 and point 9
% constraints Fz, Mx and My at all other points
%        Fx    Fy    Fz    Mx    My    Mz
sup = [[1,1];[1,2];[1,3];[1,4];[1,5];[1,6];...
                   [2,3];[2,4];[2,5];      ...
                   [3,3];[3,4];[3,5];      ...
                   [4,3];[4,4];[4,5];      ...
                   [5,3];[5,4];[5,5];      ...
                   [6,3];[6,4];[6,5];      ...
                   [7,3];[7,4];[7,5];      ...
                   [8,3];[8,4];[8,5];      ...
       [9,1];[9,2];[9,3];[9,4];[9,5];[9,6] ];
       

% constructing the data
beams = init_data(beam_start_pt, beam_end_pt, E, A, Iy, Iz, Iyz, GJ, alpha);

%% solve the system
% [d,d_lc,felem,fsup,K]
[~,delem,felem,fsup,K] = solve_structure(beams,fext,sup,cyclic,verbose);

%% save the results
if( ispc() == 1 )
	save(strcat(data_path,'\Kg_frame_beams.mat'), 'K', '-ascii');
else
	save(strcat(data_path,'/Kg_frame_beams.mat'), 'K', '-ascii');
end

end


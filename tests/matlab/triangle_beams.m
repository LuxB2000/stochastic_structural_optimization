function [] = triangle_beams( path, verbose )
%
%           --> 12kN
%         /|     _
%        / |     |
%       /  |     |
%      /   |     | 2m
%     -----       _
%    ///  |
%     <--->
%      3.5m
% 3 beams

%% defining the structure
% nodes
p1 = [0,0,0];
p2 = [3.5,0,0];
p3 = [3.5,2,0];
% topology of the structure
beam_start_pt = [p1; p2; p3];
beam_end_pt =   [p2; p3; p1];


% structural properties of the beams
E = 1;
A = 2400E-6; % in m^2
Iy = 1;% 1.2;  % TODO: need to find real values
Iz = 1;% 1.3;  % TODO: need to find real values
Iyz = 0;% 1.4; % TODO: need to find real values
GJ = 0;% 1.5;    % TODO: need to find real values
alpha = 0; % in degrees

% the structure is not cyclic
cyclic = 1;

% external force applied on the structure
fext = [1,3,12E3]; % force at point 3, along the direction X, amplitude: 12E3

% supports and constraints
sup = [[1,1];[1,2];[1,3];[1,4];[1,5];[1,6];...
       [2,2];[2,3];[2,4];[2,5];[2,6]; ...
       [3,3];[3,4];[3,5];[3,6]];

% constructing the data
beams = init_data(beam_start_pt, beam_end_pt, E, A, Iy, Iz, Iyz, GJ, alpha);

%% solve the system
[delem,felem,fsup,K] = solve_structure(beams,fext,sup,cyclic,verbose);

%% save the resultes
if( ispc() == 1 )
	save(strcat(path,'\Kg_triangle_beams.mat'), 'K', '-ascii');
else
	save(strcat(path,'/Kg_triangle_beams.mat'), 'K', '-ascii');
end

end


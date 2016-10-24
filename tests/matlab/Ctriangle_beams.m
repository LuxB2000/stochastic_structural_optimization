function [ output_args ] = Ctriangle_beams( data_path,verbose )
%
%           --> 12N
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
E = 1.1;
A = 23; % in m^2
Iy = 1.2;
Iz = 1.3;
Iyz = 0; % TODO: need to find real values
GJ = 1.4;
alpha = 0; % in degrees

% the structure is not cyclic
cyclic = 1;

% external force applied on the structure
fext = [1,3,12]; % force at point 3, along the direction X, amplitude: 12E3

% supports and constraints
sup = [[1,1];[1,2];[1,3];[1,4];[1,5];[1,6];...
             [2,2];[2,3];[2,4];[2,5];[2,6]; ...
                   [3,3];[3,4];[3,5];[3,6]];

% constructing the data
beams = init_data(beam_start_pt, beam_end_pt, E, A, Iy, Iz, Iyz, GJ, alpha);

%% solve the system
[d,dlc,felem,fsup,K] = solve_structure(beams,fext,sup,cyclic,verbose);
felem = felem(:);
dlc = dlc(:);

%% save the results
if( ispc() == 1 )
    p='\';
else
    p='/';
end
save(strcat(data_path,p,'Kg_Ctriangle_beams.mat'), 'K', '-ascii');
save(strcat(data_path,p,'disp_Ctriangle_beams.mat'), 'd', '-ascii');
save(strcat(data_path,p,'fsup_Ctriangle_beams.mat'), 'fsup', '-ascii');
save(strcat(data_path,p,'felem_Ctriangle_beams.mat'), 'felem', '-ascii');
save(strcat(data_path,p,'disp_lc_Ctriangle_beams.mat'), 'dlc', '-ascii');


end


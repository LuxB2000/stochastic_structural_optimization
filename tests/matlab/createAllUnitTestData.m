%
% This script will create all the data needed by the unit tests. The
% numerical values are generated by using the code presented in "TODO".
%

% clear the workspace
clear all;
close all;

% constants
script_path = cd();
if( ispc() == 1 )
	k = strfind(script_path,'\');
elseif( isunix()== 1 )
	k = strfind(script_path,'/');
end
data_path = strcat(script_path(1:k(end)),'data');
verbose = 0;


%% verify the presence of data folder
t = exist(data_path,'dir');
if( t == 0 ) % the folder doesn't exist, create it
    mkdir(data_path);
end

%% Build, evaluate and write the matrix for different scructures
transformed_beam(data_path,verbose);
% two_horizontal_beams(data_path,verbose);


%% code from: "A 3D Finite Beam Element for the Modelling of Composite Wind Turbine Wings" - R. DE FRIAS LOPE
%% 3D BEAM ELEMENT Fiber-Reinforced Materials [ko] and [mo]
% original code from: "A 3D Finite Beam Element for the Modelling of 
% Composite Wind Turbine Wings" - R. DE FRIAS LOPE
function [ko,mo,Tk]=FR_Beam_Element(EA,EIy,EIyz,EIz,GJ,...
    FT,LT,AT,m,I1,I2,alpham,yt,zt,yc,zc,yg,zg,a,start_pt,end_pt)
% General Axis: Y-Y,Z-Z (Flap,Lag)
% Mass Inertia Principal Axis: 1-1,2-2
%
% INPUT:
%
% Bending stiffness around T (general axis)
% Mass inertia aroung G (principal mass inertia axis)
% mass inertia principal axes orientation (anticlockwise from ... % reference system YY,ZZ) in deg
% Position of T, C and G measured from O in General Axis
%
% Units:m;N;kg
%%
alpham=alpham*pi/180;       % alpham in rad
%  C position in principal axis measured from G
y1c=(yc-yg)*cos(alpham)+(zc-zg)*sin(alpham);
z2c=-(yc-yg)*sin(alpham)+(zc-zg)*cos(alpham);
%% Stiffness and Mass Matrix
% Beam element stiffness matrix in local axes [kel]
% u referred to T and v,w referred to C in general axis
% Beam element mass matrix in local axes [mel]

% u referred to G and v,w referred to C in mass inertia principal axes
L = sqrt( sum( (end_pt-start_pt).^2 ) );
Cx = (end_pt(1)-start_pt(1))/L;
Cy = (end_pt(2)-start_pt(2))/L;
Cz = (end_pt(3)-start_pt(3))/L;
Cxz = sqrt(Cx^2+Cz^2) + eps;
s = sin(alpham);
c = cos(alpham);
%tk=[1 0 0 0 zt -yt; 0 1 0 -zc 0 0; 0 0 1 yc 0 0;... 
%    0 0 0 1 0 0; 0 0 0 0 1 0; 0 0 0 0 0 1];
tk=[      Cx           ,   Cy  ,        Cz          ; ...
    (-Cx*Cy*c-Cz*s)/Cxz,  Cxz*c, (-Cy*Cz*c+Cx*s)/Cxz; ...
    ( Cx*Cy*s-Cz*c)/Cxz, -Cxz*s, ( Cy*Cz*s+Cx*c)/Cxz];

Tk= [ tk zeros(3) zeros(3) zeros(3); zeros(3) tk zeros(3) zeros(3); zeros(3) zeros(3) tk zeros(3); zeros(3) zeros(3) zeros(3) tk]; % transformation matrix

tm=[1 0 0 0 zg -yg; 0 1 0 -zc 0 0; 0 0 1 yc 0 0;... 
    0 0 0 1 0 0; 0 0 0 0 1 0; 0 0 0 0 0 1];
qm=[1 0 0 0 0 0; 0 cos(alpham) sin(alpham) 0 0 0;...
    0 -sin(alpham) cos(alpham) 0 0 0; 0 0 0 1 0 0;...
    0 0 0 0 cos(alpham) sin(alpham); 0 0 0 0 -sin(alpham) cos(alpham)];
Tm= [ tm zeros(6); zeros(6) tm];
Qm=[qm zeros(6); zeros(6) qm];


kel11=[ EA/a 0 0 AT/a 0 0;...
        0 12*EIz/a^3 12*EIyz/a^3 0 -6*EIyz/a^2 6*EIz/a^2;...
        0 12*EIyz/a^3 12*EIy/a^3 0 -6*EIy/a^2 6*EIyz/a^2;...
        AT/a 0 0 GJ/a FT/a -LT/a;...
        0 -6*EIyz/a^2 -6*EIy/a^2 FT/a 4*EIy/a -4*EIyz/a;...
        0 6*EIz/a^2 6*EIyz/a^2 -LT/a -4*EIyz/a 4*EIz/a];
kel12=[ -EA/a 0 0 -AT/a 0 0;...
        0 -12*EIz/a^3 -12*EIyz/a^3 0 -6*EIyz/a^2 6*EIz/a^2;...
        0 -12*EIyz/a^3 -12*EIy/a^3 0 -6*EIy/a^2 6*EIyz/a^2;...
        -AT/a 0 0 -GJ/a -FT/a LT/a;...
        0 6*EIyz/a^2 6*EIy/a^2 -FT/a 2*EIy/a -2*EIyz/a;...
        0 -6*EIz/a^2 -6*EIyz/a^2 LT/a -2*EIyz/a 2*EIz/a];
kel22=[ EA/a 0 0 AT/a 0 0;...
        0 12*EIz/a^3 12*EIyz/a^3 0 6*EIyz/a^2 -6*EIz/a^2;...
        0 12*EIyz/a^3 12*EIy/a^3 0 6*EIy/a^2 -6*EIyz/a^2;...
        AT/a 0 0 GJ/a FT/a -LT/a;...
        0 6*EIyz/a^2 6*EIy/a^2 FT/a 4*EIy/a -4*EIyz/a;...
        0 -6*EIz/a^2 -6*EIyz/a^2 -LT/a -4*EIyz/a 4*EIz/a];
kel  =[kel11 kel12; kel12' kel22];


rot=I1+I2+((z2c)^2+(y1c)^2)*m;
matA=[m*a/3 0 0 0 0 0;
      0 (13*a^2*m+42*I2)/35/a 0 7*z2c*m*a/20 0 11*a^2*m/210+I2/10;
      0 0 (13*a^2*m+42*I1)/35/a -7*y1c*m*a/20 -11*a^2*m/210-I1/10 0;
      0 7*z2c*m*a/20 -7*y1c*m*a/20 a*rot/3 a^2*y1c*m/20 a^2*z2c*m/20;
      0 0 -11*a^2*m/210-I1/10 a^2*y1c*m/20 a*(a^2*m+14*I1)/105 0
      0 11*a^2*m/210+I2/10 0 a^2*z2c*m/20 0 a*(a^2*m+14*I2)/105];
matB=[m*a/6 0 0 0 0 0;
      0 (9*a^2*m-84*I2)/70/a 0 3*z2c*m*a/20 0 13*a^2*m/420-I2/10;
      0 0 (9*a^2*m-84*I1)/70/a -3*y1c*m*a/20 -13*a^2*m/420-I1/10 0;
      0 3*z2c*m*a/20 -3*y1c*m*a/20 a*rot/6 a^2*y1c*m/30 a^2*z2c*m/30;
      0 0 13*a^2*m/420-I1/10 -a^2*y1c*m/30 -a*(3*a^2*m+14*I1)/420 0
      0 -13*a^2*m/420+I2/10 0 -a^2*z2c*m/30 0 -a*(3*a^2*m+14*I2)/420];
matC=[m*a/3 0 0 0 0 0;
      0 (13*a^2*m+42*I2)/35/a 0 7*z2c*m*a/20 0 -11*a^2*m/210-I2/10;
      0 0 (13*a^2*m+42*I1)/35/a -7*y1c*m*a/20 11*a^2*m/210+I1/10 0;
      0 7*z2c*m*a/20 -7*y1c*m*a/20 a*rot/3 -a^2*y1c*m/20 -a^2*z2c*m/20;
      0 0 11*a^2*m/210+I1/10 -a^2*y1c*m/20 a*(a^2*m+14*I1)/105 0
      0 -11*a^2*m/210-I2/10 0 -a^2*z2c*m/20 0 a*(a^2*m+14*I2)/105];
      
      mel= [matA matB'; matB matC];
% ORIGINAL CODE
ko=Tk'*kel*Tk;          % element stiffness matrix for O in general axes
% /ORIGINAL CODE

% ko = Tk*kel*Tk.'; % TO MATCH PREVIOUS MATLAB CODE AND BEEN COMPATIBLE
% WITH disp = K\F;

mo=Tm'*Qm'*mel*Qm*Tm;   % element mass matrix for O in general axes
end

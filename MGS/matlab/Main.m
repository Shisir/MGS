clear all; close all; clc;

addpath('mi');
addpath('data');
max_qua_level = 50;

fileName = 'sampleDataset';
filePath = strcat(fileName,'.csv');

data = csvread(filePath, 1,0);
class = data(:,1)+1; data = data(:,2:end);

dd = size(data);sampleSize = dd(1,1);
input = data;
K = 10;
CVO = cvpartition(sampleSize,'k',K);
disp('Execution started...');
for i = 1:K
    idxTrn = CVO.training(i); 
    idxTst = CVO.test(i);
    tr_fea = input(idxTrn,:) ; Tst = input(idxTst,:);
    tr_label = class(idxTrn); LabelTst = class(idxTst);
    
    [selectedFeatures, qua, g]= selectFeatures(tr_fea, tr_label, max_qua_level);
    aa{i}=[selectedFeatures ; qua; g];
    fprintf('Fold %d/%d completed\n', i,K);
    
    matFileName = strcat(fileName, '.mat');
    save(matFileName,'aa');
end
fprintf('.........\nExecution completed!!!\n');
fprintf('A mat file is saved which will be used as input to the python file for selecting features and measuring the performance.\n');
fprintf('It contains the indices of the selected candidate feature, discritized labels and MGS values.\n');
fclose('all');
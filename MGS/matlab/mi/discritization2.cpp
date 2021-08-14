#include "miinclude.h"
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    //input:
    //prhs[0] = features
    //prhs[1] = the number of quantization
    
    //output:
    //plhs[0] = discritized value
    //plhs[1] = degres of fredom(unique value)
    
    if(nrhs!=2) mexErrMsgTxt("invalid input");
    
    double *pt2 = mxGetPr(prhs[0]),*pt1;
    double minVal=pt2[0],maxVal = pt2[0],step,Q,temp;
    int lenght = mxGetNumberOfElements(prhs[0]);
   
    for(int i=1; i<lenght; i++)
    {
        temp = pt2[i];
        if(temp<minVal) minVal = temp;
        else if(temp>maxVal) maxVal = temp;
    }
     
    Q = mxGetScalar(prhs[1]); 
    step = (maxVal-minVal)/Q;
    
    plhs[0] = mxCreateDoubleMatrix(lenght,1,mxREAL);
    pt1 = mxGetPr(plhs[0]);
    double disVal,secondDis;
    int* mark = new int[Q+1];
    int pos;
    double doublePos,uniq=0;
    for(int i=0; i<=Q; i++) mark[i]=0;
    for(int i=0; i<lenght; i++)
    {
        if(pt2[i]==minVal) pos = 1;
        else if(pt2[i]==maxVal) pos = (int)Q;
        else
        {   
            disVal = pt2[i] - minVal;
            pos = (int)(disVal/step + 1);
//             doublePos = disVal/step;
//             if(pos==doublePos) pos++;
            secondDis = disVal - (pos*step);
            if(secondDis>(pos-1)*0.0000000001) pos = pos+1;
        }
        pt1[i] = (double)(pos);
        
        if(nlhs>1) //calculate degrees of fredom
        {
            
                if(mark[pos]==0) 
                {     
                    uniq++;
                    mark[pos]=1;
                }

             plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
            double *p = mxGetPr(plhs[1]);
            p[0] = uniq;
        }
    }   
}
from sys import stdout
import pickle
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

from scipy.signal import savgol_filter

from sklearn.cross_decomposition import PLSRegression
from sklearn.model_selection import cross_val_predict
from sklearn.metrics import mean_squared_error, r2_score

filename='pls_model.dat'
open = 't.csv'
#Sindhri Mango DM.csv';
data = pd.read_csv(open)
w1 = []
w2 = []

for x in range(0,1):
    yR = 1
    xl = 2 #174 #149
    xH = -1
    Rst = 140
    # Get reference values
    Y = pd.DataFrame.as_matrix(data.iloc[:, yR])
    # Get spectra
    X = pd.DataFrame.as_matrix(data.iloc[:, xl:xH])#852-975

    # Get wavelengths (They are in the first line which is considered a header from pandas)
    wl = np.array(list(data)[xl:xH])
    print(Y[:5])
    print(wl[:])
    w1.insert(x,wl[0])
    w2.insert(x,wl[-1])
    print('1')
    
    # Calculate derivatives
    X1 = savgol_filter(X, 5, polyorder = 2, deriv=1)
    X2 = savgol_filter(X1, 5, polyorder = 2,deriv=2)
    
    print("X2")
    print(X2)
   # np.savetxt(open + "_2Der.csv", np.row_stack(X2), delimiter=",", fmt='%s', )
    #np.savetxt("2NDdERVIATIC.csv", np.row_stack((w1, w2, RTwo, MSE, SEPP, RPDD, BIA, Rcalib, RCV, Mcalib, MCV)), delimiter=",", fmt='%s', )
    
    # Plot second derivative
    plt.figure(figsize=(8,4.5))
    with plt.style.context(('ggplot')):
        plt.plot(wl, X.T)
        plt.xlabel('Wavelength (nm)')
        plt.ylabel('D2 Absorbance')
    plt.show()
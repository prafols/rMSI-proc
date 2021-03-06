/*************************************************************************
 *     rMSIproc - R package for MSI data processing
 *     Copyright (C) 2014 Pere Rafols Soler
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

#ifndef MULTI_THREAD_WORKER_H
  #define MULTI_THREAD_WORKER_H

#include <Rcpp.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "rmsicdataio.h"

class ThreadingMsiProc
{
  public:
    ThreadingMsiProc();
    ThreadingMsiProc(int numberOfThreads, bool overWriteRamdisk, Rcpp::StringVector fileNames, int massChannels, int *numRows, Rcpp::String dataType );
    ~ThreadingMsiProc();
    
  protected:
    //Pure virtual function to be implemented in ThreadingMsiProc class derivations.
    virtual void ProcessingFunction(int threadSlot);
    
    //Function to control threaded execution
    void runMSIProcessingCpp();
    
    int *iCube; //This vector will porvide which cube ID is processing each thread
    CrMSIDataIO::DataCube **cubes; //Array of data cubes pointer, the length of this array will be the number of processing threads.
    CrMSIDataIO *ioObj; //Data access object
    int *CubeFirstRowID;
    int numOfThreadsDouble; //The double of used number of threads
    
  private:  
    //The function to be executed for each thread. 
    //Data will be accessed from each thread using in-class member data and the index provided as threadSlot parameter.
    void ProcessingThread( int threadSlot );
    
    //Function to suspend main thread execution until some thread ends.
    void WaitForSomeThreadEnd();
    
    std::mutex mtx; //Lock mechanism for signalling bDataReady vector
    bool *bDataReady; //This vector will contain true when a worker thread completes a datacube processing
    bool *bRunningThread; //Keep track if a thread is runnning for a data slot
    
    //Condition variable to notify thread ends
    std::condition_variable  life_end_cond;
    std::mutex               life_end_mutex;
    bool                       life_end;
    std::thread *tworkers; //Thread objects
    bool bDataOverWrite;
};
  
#endif
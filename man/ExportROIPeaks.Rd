% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/ExportROISummary.R
\name{ExportROIPeaks}
\alias{ExportROIPeaks}
\title{ExportROIPeaks.}
\usage{
ExportROIPeaks(pkmat, idlist, out_path = getwd(), normalization = NULL)
}
\arguments{
\item{pkmat}{an rMSIproc peak matrix object.}

\item{idlist}{a list of pixel ID's in each ROI using the format returned by ExportROIAverages.}

\item{out_path}{disk path where the results will be stored.}

\item{normalization}{a text string with the name of desired normalization to apply at output files.}
}
\description{
Export a peak matrix summary as CSV files.
An average and standard deviation of each ROI is calculated for intensity, area and SNR peak matrices.
The results are stored as tables in CSV files.
}

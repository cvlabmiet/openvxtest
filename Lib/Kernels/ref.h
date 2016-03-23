/*
  File: ref.h
  Содержит объявления эталонных реализаций функций OpenVX. Функции выполняются только на RISC.

  Author: Роман Голованов

  Date: 19 Августа 2015
*/
#ifndef __REF_H__
#define __REF_H__

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "../Common/openvx/vx.h"
#include "../Common/openvx/vx_types.h"

#include "../Common/types.h"

///////////////////////////////////////////////////////////////////////////////
//                    ПРИМЕР РЕАЛИЗОВАННОЙ ФУНКЦИИ
/*
    Function: ref_Threshold
    Binary:
    Преобразование изображения в бинарное в зависимости от порога. Если яркость
    пикселя больше порога, то значение соответствующего пикселя выходного изображения
    устанавливается в 255, иначе в 0.

    Range:
    Преобразование изображения в бинарное в зависимости от порога. Если яркость
    пикселя больше верхнего порога и меньше нижнего, то значение соответствующего пикселя выходного изображения
    устанавливается в 0, иначе в 255

    Parameters:
        src_image           - входное изображение;
        dst_image           - выходное изображение;
        thresh              - структура, состоящая из трёх полей:
        - значение порога для binary (value);
        - значение верхнего порога для range (upper_thresholding);
        - значение нижнего порога для range (lower_thresholding).

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.
*/
vx_status ref_Threshold(const vx_image src_image, vx_image dst_image, const vx_threshold thresh);

///////////////////////////////////////////////////////////////////////////////

/*
    Function: ref_ConnectedComponentsLabeling

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_ConnectedComponentsLabeling

/*
    Function: ref_FourierTransform

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_FourierTransform

/*
    Function: ref_Moments

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_Moments

/*
    Function: ref_HuMoments

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_HuMoments

/*
    Function: ref_MatchTemplate

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_MatchTemplate

/*
    Function: ref_WatershedSegmentation

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_WatershedSegmentation

/*
    Function: ref_GrabCutSegmentation

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_GrabCutSegmentation

/*
    Function: ref_ViBeMotionDetection

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_ViBeMotionDetection

/*
    Function: ref_MOGMotionDetectionSG

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_MOGMotionDetectionSG

/*
    Function: ref_FindContours

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_FindContours

/*
    Function: ref_HoughLines

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_HoughLines

/*
    Function: ref_HoughCircles

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_HoughCircles

/*
    Function: ref_FitEllipse

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_FitEllipse

/*
    Function: ref_FitLine

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_FitLine

/*
    Function: ref_CurveDetector

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_CurveDetector

/*
    Function: ref_ApproximateWithPolyline

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_ApproximateWithPolyline

/*
    Function: ref_CurveFlexure

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_CurveFlexure

/*
    Function: ref_ConvexHull

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_ConvexHull

/*
    Function: ref_ConvexityDefects

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_ConvexityDefects

/*
    Function: ref_HOGDetector

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_HOGDetector

/*
    Function: ref_ViolaJonesDetector

    Описание фукнции

    Parameters (пример):
        src_image           - входное изображение;
        dst_image           - выходное изображение;

    Return:
        VX_SUCCESS          - в случае успешного завершения;
        VX_ERROR_INVALID_PARAMETERS - в случае некорректных данных.       
*/
// ref_ViolaJonesDetector


#endif // __REF_H__

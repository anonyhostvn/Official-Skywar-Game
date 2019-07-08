#ifndef PRIVATE_DATASTRUCTURE_EXIST
#define PRIVATE_DATASTRUCTURE_EXIST

#include <algorithm> 
#include <iostream>
#include "DataConstance.h"


template<typename _T> 
struct CoordVector ;

template<typename _T> 
struct PolarVector {
    private:
        _T Radius , Phi ; 
    
    public:
        PolarVector() {

        }
        PolarVector(_T Radius , _T Phi) {
            this->Radius = Radius ; 
            this->Phi = Phi ; 
        }
        _T GetR () {
            return this->Radius ; 
        }
        _T GetPhi () {
            return this->Phi ; 
        }

        void SetR(_T Radius) {
            this->Radius = Radius ; 
        }

        void SetPhi(_T Phi) {
            if (Phi < 0) Phi += 2 * pii ;   
            if (Phi > 2 * pii) Phi -= 2 * pii ; 
            this->Phi = Phi ; 
        }

        CoordVector<_T> ConvertToCoord() {
            CoordVector<_T> Result ; 
            Result.SetCoordX(this->Radius * cos(this->Phi)) ; 
            Result.SetCoordY(this->Radius * sin(this->Phi)) ; 
            return Result ;
        }

        void print() {
            std::cout << this->Radius << " " << this->Phi << "\n" ; 
        }
} ; 

template <typename _T>
struct CoordVector { 

    private:
        _T CoordX , CoordY ;

    public:
        CoordVector() {

        }
        CoordVector(_T x , _T y) {
            this->CoordX = x ;    
            this->CoordY = y ;
        }

        _T GetCoordX () {
            return this->CoordX ; 
        }

        void SetCoordX(_T CoordX) {
            this->CoordX = CoordX ; 
        }

        _T GetCoordY () {
            return this->CoordY ;
        }

        void SetCoordY (_T CoordY) {
            this->CoordY = CoordY ; 
        }
 
        CoordVector<_T> operator + (const CoordVector<_T> &other) {
            CoordVector<_T> res ; 
            res.SetCoordX(this->CoordX + other.CoordX) ; 
            res.SetCoordY(this->CoordY + other.CoordY) ; 
            return res ; 
        }

        _T operator ^ (const CoordVector &other) {
            return (CoordX * other.CoordY) - (CoordY * other.CoordX) ; 
        }

        _T operator * (const CoordVector &other) {
            return CoordX * other.CoordX + CoordY * other.CoordY ; 
        }

        CoordVector<_T> operator * (const _T &k) {
            return {(double) k * CoordX , (double) k * CoordY} ; 
        }

        _T SqrLeng () {
            return CoordX * CoordX + CoordY * CoordY ; 
        }

        PolarVector<_T> ConvertToPolar () {
            PolarVector<_T> Res ; 
            // std::cout << "In Coord Vector to Polar Vector " << this->SqrLeng() << "\n" ; 
            Res.SetR (sqrt(this->SqrLeng()) ) ;
            // _T Phi = acos((float) this->CoordX / Res.GetR()) ; 
            _T Phi = (Res.GetR() > 0) ? acos((float) this->CoordX / Res.GetR()) : 0 ; 
            if (this->CoordY < 0) Phi = 2 * pii - Phi ; 

            Res.SetPhi(Phi) ; 
            return Res ;
        }
        // PolarVector<_T> ConvertToPolar () ; 


        void print() {
            // printf("%d %d \n" , CoordX , CoordY) ; 
            std::cout << CoordX << " " << CoordY << "\n" ; 
        }
} ; 

template <typename _T>
struct CoordPoint {
    private:
        _T CoordX , CoordY ; 

    public:
        CoordPoint() {

        } 
        CoordPoint(_T x , _T y) {
            this->CoordX = x ; 
            this->CoordY = y ; 
        }

        _T GetX () { return CoordX ; } 
        _T GetY () {return CoordY ; } 
        void SetX (_T x) {this->CoordX = x  ; } 
        void SetY (_T y) {this->CoordY = y ; }
        void print () {
            // printf("%d %d \n" , CoordX , CoordY) ;
            std::cout << CoordX << " " << CoordY << "\n" ;  
        }
        CoordVector<_T> MakeVector (CoordPoint<_T> &Other) {
            CoordVector<_T> Res = {Other.GetX() - CoordX , Other.GetY() - CoordY} ; 
            return Res ; 
        }

        _T SqrDistanceTo (CoordPoint& Other) {
            return (Other.GetX() - CoordX) * (Other.GetX() - CoordX) + (Other.GetY() - CoordY) * (Other.GetY() - CoordY) ; 
        }
} ; 

#endif
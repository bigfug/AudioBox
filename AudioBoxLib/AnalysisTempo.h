#pragma once

#include "Analysis.h"
#include "Average.h"

class AnalysisTempo : public Analysis
{
protected:
	double					 mLastBeat;
	double					 mNextBeat;
	double					 mNextBeat2;
	float					 mBeatPhase;
//	float					 mBeatPhase2;
	float					 mStartBPM;
	float					 mBPM;
	double					 mBeatLength;
	double					 mBeatMargin;
	bool					 mIsBeat;
	float					 mSyncConfidence;
//	float					 mLastSyncPower;
//	DWORD					 mLastBeatCorrection;
//	DWORD					 mLastTempoCorrection;
	AverageFloat			 mImpulsePowerAverage;
	AverageFloat			 mBeatAdjustAverage;
	int						 mBeatMap[ 17 ];
	int						 mLastBeatMapOffset;
	float					 mBeatOffset[ 1024 ];

	inline long beatDiff( DWORD pTS1, DWORD pTS2 ) const
	{
		return( (long)mBeatLength - (long)( pTS1 - pTS2 ) );
	}

	static DWORD ms2bpm( DWORD pMs )
	{
		return( 60000 / pMs );
	}

	static DWORD bpm2ms( DWORD pBpm )
	{
		return( 60000 / pBpm );
	}

public:
	AnalysisTempo( void );

	virtual ~AnalysisTempo( void );

	bool initialise( const int pSampleRate, const int pSamplesPerFrame );

	void deinitialise( void );

	void processImpulse( const PtTimestamp pTimeStamp, const float pPower, const bool pLocked );
	void processTempo( const float pBeatLength, const float pConfidence );
	void processTime( const PtTimestamp pTimeStamp, float &pBeatOffset );
	void setBeat( const PtTimestamp pTimeStamp );

	inline float getSyncConfidence( void ) const
	{
		return( mSyncConfidence );
	}

	inline float getCurrentBpm( void ) const
	{
		return( mBPM );
	}

	inline float getBeatPhase( void ) const
	{
		return( mBeatPhase );
	}

	inline DWORD getCurrentBeatLength( void ) const
	{
		return( mBeatLength );
	}

	inline bool isBeat( void ) const
	{
		return( mIsBeat );
	}
};

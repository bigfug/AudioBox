#pragma once

#include "Analysis.h"
#include "FFT.h"
#include "Average.h"
#include "AnalysisTempo.h"

using namespace std;

#define		COUNT_VALUES		(512)

#define		BPM_START			(120)
#define		BPM_SCAN_MIN		(15)
#define		BPM_SCAN_MAX		(400)

#define		BPM_ENTRY_COUNT		(15)

#define		BPM_MAX_CNT			(20)
#define		BPM_NEW_CNT			(5)

typedef struct
{
	DWORD		mTimeStamp;
	float		mPower;
} BeatEntry;

typedef struct
{
	UINT		mBpm;
	float		mValue;
} BpmEntry;

typedef vector<BeatEntry>								BeatEntryVector;

class AnalysisBeat : public Analysis
{
protected:
	AnalysisTempo			 mAnalysisTempo;

	bool					 mInBeat;
	bool					 mIsBeat;
	bool					 mBeatStart;
	bool					 mBeatAscending;
	float					 mBeatLastValue;
	float					 mBeatMax;
	float					 mBeatRelMax;
	DWORD					 mBeatMaxTime;
	DWORD					 mBeatStartTime;
	DWORD					 mBeatSamples;

	wxCriticalSection		 mBeatLock;
	BeatEntryVector			 mBeats;
	float					 mBpmMap[ COUNT_VALUES ];
	BpmEntry				 mBpmEntries[ COUNT_VALUES ];
	float					 mBpm;
	float					 mLastBpm;
	DWORD					 mBeatLength;

	float					 mCalcBpm;
	float					 mCalcTempoConfidence;
	float					 mCalcSyncConfidence;

	UINT					 mBeatsAdded;
	DWORD					 mLastTime;

	float					 mBpmCur;
	int						 mBpmCurCnt;
	float					 mBpmNew[ BPM_NEW_CNT ];
	int						 mBpmNewCnt[ BPM_NEW_CNT ];

	UINT					 mBpmMin;
	UINT					 mBpmMax;

	float					 mBeatOffset;
	bool					 mBeatLocked;

	int						 mBeat;

	static DWORD ms2bpm( DWORD pMs )
	{
		return( 60000 / pMs );
	}

	static DWORD bpm2ms( DWORD pBpm )
	{
		return( 60000 / pBpm );
	}

	void reset( void );
	void addBeat( DWORD pTime, float pPower );

	static int __cdecl sortBpmEntry( const void *p1, const void *p2 )
	{
		const BpmEntry *e1 = reinterpret_cast<const BpmEntry *>( p1 );
		const BpmEntry *e2 = reinterpret_cast<const BpmEntry *>( p2 );

		if( e1->mValue > e2->mValue ) return( -1 );
		if( e1->mValue < e2->mValue ) return( +1 );

		return( 0 );
	}

public:
	AnalysisBeat( void );

	virtual ~AnalysisBeat( void );

	bool initialise( const int pSampleRate, const int pSamplesPerFrame );

	void deinitialise( void );

	void processData( float pValue, float pAverage, PtTimestamp pTimeStamp, long pWindowSize );
	void processBeats( void );
	bool processTime( PtTimestamp pTimeStamp );

	void setBeat( void );

	bool isBeat( void )
	{
		bool	Temp = mIsBeat;

		mIsBeat = false;

		return( Temp );
	}

	inline int getBeat( void ) const
	{
		return( mBeat );
	}

	inline const float getBeatsPerMinute( void )
	{
		return( mCalcBpm );

		//return( mBpm );
	}

	inline int getTempoConfidence( void ) const
	{
		return( mCalcTempoConfidence * 100.0f );
	}

	inline float getSyncConfidence( void ) const
	{
		return( mCalcSyncConfidence );
	}

	inline float *getBpmMap( void ) const
	{
		return( (float *)&mBpmMap );
	}

	inline float getBeatPhase( void ) const
	{
		return( mAnalysisTempo.getBeatPhase() );
	}

	inline void addBeatOffset( const float pOffset )
	{
		mBeatOffset += pOffset;
	}

	inline void setBeatLocked( const bool pLocked )
	{
		mBeatLocked = pLocked;
	}
};

#pragma once

typedef struct
{
	float		mIndex;
	float		mValue;
	float		mCertainty;
	float		mRelValue;
	int			mHighIndex;
	int			mWidth;
} Peak;

enum
{
	PEAK_POSITIVE = 0,
	PEAK_NEGATIVE = 1
};

class Peaks
{
private:
	float			*mBuffer;
	float			*mMovement;
	int				*mActive;
	Peak			*mPeaks;
	int				 mNumVals;
	const int		 mNumPeaks;
	int				 mSampleRate;
	int				 mNumCount;
public:
	float			 mNotes[ 12 ];

	Peaks( const int pNumVals, const int pNumPeaks )
		: mNumPeaks( pNumPeaks ), mNumCount( 0 )
	{
		int NumPeaks = pNumVals / 2;

		this->mBuffer = new float[ pNumVals ];
		this->mMovement = new float[ pNumVals ];
		this->mPeaks  = new Peak[ NumPeaks ];
		this->mActive = new int[ pNumVals ];

		this->mNumVals    = pNumVals;
		this->mSampleRate = 0;

		memset( this->mBuffer, 0, sizeof(float) * mNumVals );
		memset( this->mMovement, 0, sizeof(float) * mNumVals );
		memset( this->mPeaks, 0, sizeof(Peak) * NumPeaks );
		memset( this->mActive, 0, sizeof(int) * mNumVals );
	}

	~Peaks( void )
	{
		delete this->mActive;
		delete this->mPeaks;
		delete this->mMovement;
		delete this->mBuffer;
	}

	inline void setSampleRate( const int pSampleRate )
	{
		mSampleRate = pSampleRate;
	}

	void findAllPeaks( const float *pInput )
	{
		float		 LastVal = 0.0f;
		Peak		*CurPeak = mPeaks;
		int			 Direction = PEAK_POSITIVE;
		int			 IdxCount;
		float		 ValTotal;
		int			 PeakStart;
		float		 PeakTotal;

		mNumCount = 0;
		IdxCount  = 0;
		ValTotal  = 0.0f;
		PeakStart = 0;
		PeakTotal = 0.0f;

		for( int i = 0 ; i < mNumVals ; i++ )
		{
			if( ( i == mNumVals - 1 && CurPeak->mValue ) || ( pInput[ i ] > LastVal && Direction == PEAK_NEGATIVE ) )
			{
				CurPeak->mIndex    = PeakStart + ( ValTotal / PeakTotal ) - 1.0f;
				CurPeak->mWidth    = IdxCount;
				CurPeak->mRelValue = CurPeak->mValue - max( CurPeak->mRelValue, LastVal );

				CurPeak++;

				mNumCount++;

				IdxCount  = 0;
				ValTotal  = 0.0f;
				PeakTotal = 0.0f;
				PeakStart = i;

				CurPeak->mRelValue  = pInput[ i ];

				Direction = PEAK_POSITIVE;
			}
			else if( pInput[ i ] < LastVal && Direction == PEAK_POSITIVE )
			{
				CurPeak->mHighIndex = i - 1;
				CurPeak->mValue = pInput[ i - 1 ];

				Direction = PEAK_NEGATIVE;
			}

			IdxCount++;
			PeakTotal += pInput[ i ];
			ValTotal  += pInput[ i ] * ( i - PeakStart + 1 );

			LastVal = pInput[ i ];
		}
	}

	static int sortPeakFunc( const void *pPeak1, const void *pPeak2 )
	{
		if( ((Peak *)pPeak1)->mValue < ((Peak *)pPeak2)->mValue )
		{
			return( 1 );
		}

		if( ((Peak *)pPeak1)->mValue > ((Peak *)pPeak2)->mValue )
		{
			return( -1 );
		}

		return( 0 );
	}

	inline void sortPeaksByValue( void )
	{
		qsort( mPeaks, mNumCount, sizeof(Peak), Peaks::sortPeakFunc );
	}

	static int sortPeakFuncRelVal( const void *pPeak1, const void *pPeak2 )
	{
		if( ((Peak *)pPeak1)->mRelValue < ((Peak *)pPeak2)->mRelValue )
		{
			return( 1 );
		}

		if( ((Peak *)pPeak1)->mRelValue > ((Peak *)pPeak2)->mRelValue )
		{
			return( -1 );
		}

		return( 0 );
	}

	void sortPeaksByRelativeValue( void )
	{
		qsort( mPeaks, mNumCount, sizeof(Peak), Peaks::sortPeakFuncRelVal );
	}

	static int sortPeakFuncIndex( const void *pPeak1, const void *pPeak2 )
	{
		if( ((Peak *)pPeak1)->mIndex > ((Peak *)pPeak2)->mIndex )
		{
			return( 1 );
		}

		if( ((Peak *)pPeak1)->mIndex < ((Peak *)pPeak2)->mIndex )
		{
			return( -1 );
		}

		return( 0 );
	}

	void sortPeaksByIndex( void )
	{
		qsort( mPeaks, mNumCount, sizeof(Peak), Peaks::sortPeakFuncIndex );
	}

	void findPeaks( const float *pInput, const int pStart, const int pEnd )
	{
		float		DivVal;

		this->findAllPeaks( pInput );

		this->sortPeaksByRelativeValue();

		for( int i = 0 ; i < mNumCount ; i++ )
		{
/*
			for( int j = i + 1 ; j < mNumCount ; j++ )
			{
				if( mPeaks[ i ].mIndex < mPeaks[ j ].mIndex )
				{
					RemVal = modf( mPeaks[ j ].mIndex / mPeaks[ i ].mIndex, &IntVal );
				}
				else
				{
					RemVal = modf( mPeaks[ i ].mIndex / mPeaks[ j ].mIndex, &IntVal );
				}

				if( RemVal > 0.1f && RemVal < 0.9f ) break;
			}
*/
/*
			DivVal = mPeaks[ i ].mIndex / mPeaks[ i + 1 ].mIndex;

			if( DivVal > 0.45f && DivVal < 0.55f )
			{
				float		Temp = mPeaks[ i ].mIndex;

				mPeaks[ i ].mIndex = mPeaks[ i + 1 ].mIndex;
				mPeaks[ i + 1 ].mIndex = Temp;
			}
*/
			// TODO mCertainty is < 0.0f

			if( i + 1 < mNumCount )
			{
				DivVal = mPeaks[ i ].mIndex / mPeaks[ i + 1 ].mIndex;

				if( ( ( DivVal > 1.95f && DivVal < 2.05f ) || ( DivVal > 0.45f && DivVal < 0.55f ) ) && i + 2 < mNumCount )
				{
					mPeaks[ i ].mCertainty = 1.0f - ( mPeaks[ i + 2 ].mValue / mPeaks[ i ].mValue );
				}
				else
				{
					mPeaks[ i ].mCertainty = 1.0f - ( mPeaks[ i + 1 ].mValue / mPeaks[ i ].mValue );
				}
			}
			else
			{
				mPeaks[ i ].mCertainty = mPeaks[ i ].mValue;
			}

//			mPeaks[ i ].mCertainty = 1.0f - ( mPeaks[ i + 1 ].mValue / mPeaks[ i ].mValue );
		}
	}

	void measurePeaks( const float *pInput, const int pStart, const int pEnd )
	{
		float		PeakCertainty;
		int			i, j;

		assert( mSampleRate > 0 );

		for( i = 0 ; i < 12 ; i++ )
		{
			this->mNotes[ i ] = 0.0f;
		}

		this->findAllPeaks( pInput );

		this->sortPeaksByValue();

		for( i = 0 ; i < mNumCount && mPeaks[ i ].mRelValue > 0.1f ; i++ )
		{
			PeakCertainty = mPeaks[ i ].mRelValue;

			float		NoteFreq = mPeaks[ i ].mIndex * ( ( (float)this->mSampleRate / 2.0f ) / (float)this->mNumVals );
			float		CurrFreq = 27.50f; // A0
			float		LastFreq = 27.50f;
			int			MidiNote = 21;
			float		Margin;

			while( CurrFreq < NoteFreq )
			{
				LastFreq  = CurrFreq;
				CurrFreq *= 1.0594630943592952645618252949463f;

				MidiNote++;
			}

			Margin  = CurrFreq - LastFreq;

			if( fabs( NoteFreq - LastFreq ) < fabs( NoteFreq - CurrFreq ) )
			{
				CurrFreq = LastFreq;

				MidiNote--;
			}

			Margin = ( Margin / 100.0f ) * 10.0f;

			if( NoteFreq > CurrFreq - Margin && NoteFreq < CurrFreq + Margin )
			{
				/*
				this->mPeaks[ i ].mIndex        = CurrFreq / ( ( (float)this->mSampleRate / 2.0f ) / (float)this->mNumVals );
				this->mPeaks[ i ].mValue        = MidiNote;
				this->mPeaks[ i ].mCertainty    = PeakCertainty;
				*/

				int FreqIndex = (int)this->mPeaks[ i ].mIndex;

				this->mBuffer[ MidiNote ] += PeakCertainty;

				//this->mBuffer[ MidiNote ] = PeakCertainty;

				if( this->mBuffer[ MidiNote ] > 2.0f )
				{
					//this->mBuffer[ MidiNote ] = 2.0f;
				}

				this->mActive[ MidiNote ] = 0;

				int		NoteIndex = MidiNote % 12;

				this->mNotes[ NoteIndex ] += this->mBuffer[ MidiNote ];
			}
		}

			//this->mMovement[ i ] = ( this->mMovement[ i ] + this->mBuffer[ i ] - OldVal ) / 2;

		for( i = 0 ; i < 127 ; i++ )
		{
			if( this->mBuffer[ i ] > 0.0f )
			{
				if( this->mActive[ i ] > 0 )
				{
					this->mBuffer[ i ] *= ( 250.0f - (float)this->mActive[ i ] ) / 250.0f;;
				}

				this->mActive[ i ]++;
			}
		}

		float		LastPeakMax = 1000.0f;
		float		PeakMax;
		int			PeakMaxIndex;

		for( j = 0 ; j < mNumPeaks ; j++ )
		{
			PeakMax = 0.0f;
			PeakMaxIndex = 0;

			for( i = 0 ; i < 127 ; i++ )
			{
				if( mBuffer[ i ] > PeakMax && mBuffer[ i ] < LastPeakMax )
				{
					PeakMax = mBuffer[ i ];
					PeakMaxIndex = i;
				}
			}

			if( PeakMax > 0.15f )
			{
				this->mPeaks[ j ].mIndex = PeakMaxIndex;
			}
			else
			{
				this->mPeaks[ j ].mIndex = 0.0f;
			}

			LastPeakMax = PeakMax;
		}
	}

	inline Peak &getPeak( const int pIndex ) const
	{
		return( this->mPeaks[ pIndex ] );
	}

	inline void setPeakIndex( const int pIndex, const float pValue )
	{
		this->mPeaks[ pIndex ].mIndex = pValue;
	}

	inline float *getBuffer( void ) const
	{
		return( this->mBuffer );
	}

	inline float *getMovement( void ) const
	{
		return( this->mMovement );
	}

	inline float getNoteCertainty( const int pIndex ) const
	{
		return( this->mNotes[ pIndex ] );
	}

	inline int getPeakCount( void ) const
	{
		return( mNumCount );
	}
};


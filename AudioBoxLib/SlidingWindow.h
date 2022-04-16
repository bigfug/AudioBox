#pragma once

template <class tType> class SlidingWindow
{
protected:
	const int		 mInputSize;
	const int		 mOutputSize;
	const int		 mOutputDivisions;
	const int		 mOutputDivisionSize;
	tType			*mBuffer;
	tType			*mInputDst;
	int				 mInputCnt;
	PtTimestamp		 mTimeStamp1;
	PtTimestamp		 mTimeStamp2;
public:
	SlidingWindow( const int pInputSize, const int pOutputSize, const int pOutputDivisions )
	: mInputSize( pInputSize ),
	  mOutputSize( pOutputSize ),
	  mOutputDivisions( pOutputDivisions ),
	  mOutputDivisionSize( pOutputSize / pOutputDivisions ),
	  mInputCnt( 0 ),
	  mTimeStamp1( 0 ), mTimeStamp2( 0 )
	{
		assert( mOutputDivisionSize * mOutputDivisions == mOutputSize );

		mBuffer = new tType[ pOutputSize * 2 ];

		for( int i = 0 ; i < pOutputSize * 2 ; i++ )
		{
			mBuffer[ i ] = 0;
		}

		mInputDst = mBuffer;
	}

	virtual ~SlidingWindow( void )
	{
		delete [] mBuffer;
	}

	void addData( const tType *pInputData, PtTimestamp pTimeStamp )
	{
		// if the buffer is full move the second half to the front of the buffer

		if( mInputCnt == mOutputSize * 2 )
		{
			memcpy( mBuffer, &mBuffer[ mOutputSize ], mOutputSize * sizeof( tType ) );

			mInputDst = &mBuffer[ mOutputSize ];
			mInputCnt = mOutputSize;

			mTimeStamp1 = mTimeStamp2;
		}
		else if( mInputCnt == 0 )
		{
			mTimeStamp1 = pTimeStamp;
		}

		memcpy( mInputDst, pInputData, mInputSize * sizeof( tType ) );

		mInputDst += mInputSize;
		mInputCnt += mInputSize;

		mTimeStamp2 = pTimeStamp;
	}

	int getAvailableWindows( void ) const
	{
		return( mInputCnt == mOutputSize * 2 ? mOutputDivisions : 0 );
	}

	const tType *getWindow( const int pIndex ) const
	{
		assert( pIndex >= 0 && pIndex < mOutputDivisions );

		return( &mBuffer[ pIndex * mOutputDivisionSize ] );
	}

	PtTimestamp getWindowTime( const int pIndex ) const
	{
		assert( pIndex >= 0 && pIndex < mOutputDivisions );

		return( mTimeStamp1 + ( ( ( mTimeStamp2 - mTimeStamp1 ) / mOutputDivisions ) * pIndex ) );
	}

	long getWindowLength( void ) const
	{
		return( ( mTimeStamp2 - mTimeStamp1 ) / mOutputDivisions );
	}
};

typedef SlidingWindow<float>	SlidingWindowFloat;
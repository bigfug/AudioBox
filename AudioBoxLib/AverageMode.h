#pragma once

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

template <class tType> class AverageMode
{
	const		int			 mCount;
	int						 mCurrPos;
	tType					 mLastVal;
	tType					*mValues;
	tType					*mValuesSorted;
	tType					 mSum;
	tType					 mMin, mMax;
public:
	AverageMode( const int pCount ) : mCount( pCount ), mValues( 0 )
	{
		assert( mCount > 0 );

		mValues			= new tType[ pCount ];
		mValuesSorted	= new tType[ pCount ];

		this->reset();
	}

	~AverageMode( void )
	{
		SAFE_DELETE_ARRAY( mValues );
		SAFE_DELETE_ARRAY( mValuesSorted );
	}

	void reset( tType pValue = 0 )
	{
		mCurrPos = 0;
		mSum = 0;
		mMin = mMax = pValue;

		mLastVal = pValue;

		for( int i = 0 ; i < mCount ; i++ )
		{
			mValues[ i ] = mValuesSorted[ i ] = pValue;

			mSum += pValue;
		}
	}

	tType getAverage( void ) const
	{
		return( mSum / mCount );
	}

	tType getAverageMode( void ) const
	{
		return( mValuesSorted[ mCount / 2 ] );
	}

	tType getLastValue( void ) const
	{
		return( mLastVal );
	}

	static int __cdecl valCompare( const void *p1, const void *p2 )
	{
		const tType *v1 = reinterpret_cast<const tType *>( p1 );
		const tType *v2 = reinterpret_cast<const tType *>( p2 );

		if( *v1 < *v2 ) return( -1 );
		if( *v1 > *v2 ) return(  1 );

		return( 0 );
	}

	void addValue( const tType pData )
	{
		mLastVal = pData;

		mSum -= mValues[ mCurrPos ];
		mSum += pData;

		mValues[ mCurrPos++ ] = pData;

		if( mCurrPos == mCount )
		{
			mCurrPos = 0;
		}

		memcpy( mValuesSorted, mValues, sizeof( tType ) * mCount );

		qsort( mValuesSorted, mCount, sizeof( tType ), valCompare );

		mMin = mValuesSorted[ 0 ];
		mMax = mValuesSorted[ mCount - 1 ];
	}

	tType getMin( void ) const
	{
		return( mMin );
	}

	tType getMax( void ) const
	{
		return( mMax );
	}

	tType getSum( void ) const
	{
		return( mSum );
	}

	float getVarience( void ) const
	{
/*
		tType		Last = this->mValues[ 0 ];
		int			Switches = 0;
		int			Direction = 0;

		for( int i = 1 ; i < this->mCount ; i++ )
		{
			if( this->mValues[ i ] > Last )
			{
				if( Direction == -1 )
				{
					//Switches++;
				}

				Direction = 1;
			}
			else if( this->mValues[ i ] < Last )
			{
				if( Direction == 1 )
				{
					Switches++;
				}

				Direction = -1;
			}
			else
			{
				//Direction = 0;
			}

			Last = this->mValues[ i ];
		}

		if( Switches == 0 ) return( 0.0f );

		float Varience = (float)Switches / (float)this->mCount;

		return( Varience  );
*/
		//return( ( getAverage() - mMin ) / ( mMax - mMin ) );

		const float		BandDiff    = mMax - mMin;
		const float		BandMaxDiff = mMax - getAverage();
		const float		BandMinDiff = getAverage() - mMin;

		return( ( BandMaxDiff / BandDiff ) - ( BandMinDiff / BandDiff ) );
	}
};

typedef AverageMode<float>		AverageModeFloat;

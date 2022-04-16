#pragma once

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

template <class tType> class Average
{
	const		int			 mCount;
	int						 mCurrPos;
	tType					 mLastVal;
	tType					*mValues;
	tType					 mSum;
	tType					 mMin, mMax;
public:
	Average( const int pCount ) : mCount( pCount ), mValues( 0 )
	{
		assert( mCount > 0 );

		this->mValues = new tType[ pCount ];

		this->reset();
	}

	~Average( void )
	{
		SAFE_DELETE_ARRAY( this->mValues );
	}

	void reset( tType pValue = 0 )
	{
		this->mCurrPos = 0;
		this->mSum = 0;
		this->mMin = this->mMax = pValue;

		mLastVal = pValue;

		for( int i = 0 ; i < mCount ; i++ )
		{
			this->mValues[ i ] = pValue;

			mSum += pValue;
		}
	}

	tType getAverage( void ) const
	{
		return( mSum / mCount );
	}

	tType getLastValue( void ) const
	{
		return( mLastVal );
	}

	void addValue( const tType pData )
	{
		const tType		Removed = mValues[ mCurrPos ];

		mLastVal = pData;

		mSum -= Removed;
		mSum += pData;

		mValues[ mCurrPos++ ] = pData;

		if( mCurrPos == mCount )
		{
			mCurrPos = 0;
		}

		if( Removed == mMax )
		{
			tType		NewMax = 0;

			for( int i = 0 ; i < mCount ; i++ )
			{
				if( mValues[ i ] > NewMax ) NewMax = mValues[ i ];
			}

			mMax = NewMax;
		}

		if( Removed == mMin )
		{
			tType		NewMin = mMax;

			for( int i = 0 ; i < mCount ; i++ )
			{
				if( mValues[ i ] < NewMin ) NewMin = mValues[ i ];
			}

			mMin = NewMin;
		}
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

typedef Average<float>		AverageFloat;

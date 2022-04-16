#pragma once

template <class tType> class Convolve
{
public:
	void GaussianBlur( tType *pInput, tType *pOutput, int pCount )
	{
		pOutput[ 0 ] = ( ( pInput[ 0 ] * 15.0 ) + ( pInput[ 1 ] * 12.0 ) + ( pInput[ 2 ] * 12.0 ) ) / 39.0;
		pOutput[ 1 ] = ( ( pInput[ 0 ] * 12.0 ) + ( pInput[ 1 ] * 15.0 ) + ( pInput[ 2 ] * 12.0 ) + ( pInput[ 3 ] * 5.0 ) ) / 44.0;

		pOutput[ pCount - 2 ] = ( ( pInput[ pCount - 1 ] * 12.0 ) + ( pInput[ pCount - 2 ] * 15.0 ) + ( pInput[ pCount - 3 ] * 12.0 ) + ( pInput[ pCount - 4 ] * 5.0 ) ) / 44.0;
		pOutput[ pCount - 1 ] = ( ( pInput[ pCount - 1 ] * 15.0 ) + ( pInput[ pCount - 2 ] * 12.0 ) + ( pInput[ pCount - 3 ] * 12.0 ) ) / 39.0;

		for( int x = 2 ; x < pCount - 2 ; x++ )
		{
			pOutput[ x ] = (
				( pInput[ x - 2 ] * 5.0 ) +
				( pInput[ x - 1 ] * 12.0 ) +
				( pInput[ x     ] * 15.0 ) +
				( pInput[ x + 1 ] * 12.0 ) +
				( pInput[ x + 2 ] * 5.0 )
				) / 49.0;
		}
	}

	void Laplacian( tType *pInput, tType *pOutput, int pCount )
	{
		pOutput[ 0 ] = ( ( pInput[ 0 ] * -40.0 ) + ( pInput[ 1 ] * -23.0 ) ) / -63.0;
		pOutput[ pCount - 1 ] = ( ( pInput[ pCount - 1 ] * -40.0 ) + ( pInput[ pCount - 2 ] * -23.0 ) ) / -63.0;

		for( int x = 1 ; x < pCount - 1 ; x++ )
		{
			pOutput[ x ] = (
				( pInput[ x - 1 ] * -23.0 ) +
				( pInput[ x     ] * -40.0 ) +
				( pInput[ x + 1 ] * -23.0 )
				) / -86.0;
		}
	}
};

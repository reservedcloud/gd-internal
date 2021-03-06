#include "hookmgr.h"
#include "sdk/player.h"

std::vector<std::string> SignatureList, SignatureName;
std::vector<int> SignatureOffset, isDirectFunction;

#define ADD_SIG(Name, Signature, Offset, isDirectFunctionVal) SignatureName.push_back(Name); \
SignatureList.push_back(Signature); \
SignatureOffset.push_back(Offset); \
isDirectFunction.push_back(isDirectFunctionVal);

VOID
LoadHookMgr( )
{
	ADD_SIG( "Player:Get", "FF 50 ?? E8 92 02 00 00 FF D3 8B 0D", 12, FALSE );
	ADD_SIG( "sdk:LevelEditor", "8b 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 8b 4d ?? 64 89 0d ?? ?? ?? ?? 59 8b e5", 2, FALSE );

	//Patching the game
	ADD_SIG( "Noclip", "C2 ?? ?? 6A ?? 8B CB FF 15 ?? ?? ?? ?? 8B CB", 3, TRUE );
	ADD_SIG( "noRotation", "7B 13 F3 0F 11 49 ?? F3 0F 11 49 ?? 66 C7 81", 2, TRUE ); //libcocos2d.dll
	
	ADD_SIG( "practiceMusicHack1", "0F 85 ?? ?? ?? ?? 8B 8E ?? ?? ?? ?? 8B 01 FF 50", 0, TRUE );
	ADD_SIG( "practiceMusicHack2", "75 41 8B 8E ?? ?? ?? ?? 8B 3D ?? ?? ?? ?? FF D7", 0, TRUE );
	ADD_SIG( "practiceMusicHack3", "75 3E 8B 8B ?? ?? ?? ?? 8B 01 FF 50", 0, TRUE );
	ADD_SIG( "practiceMusicHack4", "75 0C E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 83", 0, TRUE );

	ADD_SIG( "hideAttempts", "41 74 74 65 6D 70 74 20 25 ?? ?? ?? ?? 54", 0, TRUE );
	ADD_SIG( "ignoreEsc", "8B 89 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 EC ?? 8B CC 89 65 F0", 6, TRUE );
	ADD_SIG( "noPulse", "74 4A 80 BF ?? ?? ?? ?? 00 8B 07 F3 0F 10 44 24", 0, TRUE );
	ADD_SIG( "inverseTrail", "0F 84 ?? ?? ?? ?? 85 C0 0F 84 ?? ?? ?? ?? 8D BE", 0, TRUE ); // libcocos2d.dll

	ADD_SIG( "copyHack1", "75 0E 6A 00 E8 ?? ?? ?? ?? 5E 8B E5 5D C2 04 00", 0, TRUE );
	ADD_SIG( "copyHack2", "0F 44 CA 51 FF 15 ?? ?? ?? ?? 83 C4 ?? 8B C8 E8", 0, TRUE );
	ADD_SIG( "copyHack3", "0F 95 C0 50 8B 11 FF 92 ?? ?? ?? ?? 8B 8B", 0, TRUE );

	ADD_SIG( "instantComplete", "FF 15 ?? ?? ?? ?? 8B 8F ?? ?? ?? ?? 8D 44 24 ?? 8B 35", 16, TRUE );

	ADD_SIG( "freeShopItems1", "8B 93 ?? ?? ?? ?? 2B CA 3B C1 7C 76 2B 93", 0, TRUE );
	ADD_SIG( "freeShopItems2", "8B B3 ?? ?? ?? ?? 2B B3 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B", 0, TRUE );

	ADD_SIG( "characterFilter", "E8 ?? ?? ?? ?? 80 3B ?? 75 04 33 C9 EB 0E 8B CB", 8, TRUE );
	ADD_SIG( "textLenght", "39 88 ?? ?? ?? ?? 7C 04 85 C9 7F 04", 6, TRUE );
	
	ADD_SIG( "songBypass", "68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B CF C6 84 24 ?? ?? ?? ?? 00 E8", 1, FALSE );

	// AntiCheat
	ADD_SIG( "AntiCheat1", "74 2E E8 ?? ?? ?? ?? F3 0F 10 8F", 0, TRUE );
	ADD_SIG( "AntiCheat2", "74 60 8B CB E8 ?? ?? ?? ?? 8B 0D", 0, TRUE );
	ADD_SIG( "AntiCheat3", "74 0C 8B CF E8 ?? ?? ?? ?? E9 ?? ?? ?? ?? 80", 0, TRUE );
	ADD_SIG( "AntiCheat4", "80 bf ?? ?? ?? ?? ?? 0f 85 ?? ?? ?? ?? 80 bf ?? ?? ?? ?? ?? 0f 84 ?? ?? ?? ?? 80 bf", 0, TRUE );
	ADD_SIG( "AntiCheat5", "0f 84 ?? ?? ?? ?? 80 bf ?? ?? ?? ?? ?? 0f 85 ?? ?? ?? ?? 8b 87", 0, TRUE );
	ADD_SIG( "AntiCheat6", "F2 0F 5C 87 ?? ?? ?? ?? 0F 84 ?? ?? ?? ?? 8B 87", 8, TRUE );
	ADD_SIG( "AntiCheat7", "F2 0F 5C 87 ?? ?? ?? ?? 0F 84 ?? ?? ?? ?? 8B 87", 29, TRUE );
	ADD_SIG( "AntiCheat8", "80 B9 ?? ?? ?? ?? 00 75 05 E8", 9, TRUE );
	ADD_SIG( "AntiCheat9", "74 6E 68 ?? ?? ?? ?? 53", 0, TRUE );
	ADD_SIG( "AntiCheat10", "8a c3 5b 5d c3 8d 49", 0, TRUE );
	ADD_SIG( "AntiCheat11", "0f 85 ?? ?? ?? ?? 8b 35 ?? ?? ?? ?? c6 83", 0, TRUE );


	ADD_SIG( "iconBypass1", "e8 ?? ?? ?? ?? 8b e5 5d c2 ?? ?? cc cc cc cc cc cc cc cc cc cc cc cc cc 0f b6 81", 0, TRUE );
	ADD_SIG( "iconBypass2", "e8 ?? ?? ?? ?? 8b e5 5d c2 ?? ?? cc cc cc cc cc cc cc cc cc cc cc 55 8b ec 6a ?? 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 83 ec ?? a1 ?? ?? ?? ?? 33 c5 89 45 ?? 56 50", 0, TRUE );

	ADD_SIG( "levelEdit", "75 ?? 68 ?? ?? ?? ?? ff 15 ?? ?? ?? ?? 8b d8 83 c4", 0, TRUE );
	ADD_SIG( "ignoreEsc", "e8 ?? ?? ?? ?? 83 ec ?? 8b cc 89 65 ?? 6a ?? c7 41 ?? ?? ?? ?? ?? c7 41 ?? ?? ?? ?? ?? 68 ?? ?? ?? ?? c6 01 ?? e8 ?? ?? ?? ?? c7 45 ?? ?? ?? ?? ?? 83 3d ?? ?? ?? ?? ?? 75 ?? 68 ?? ?? ?? ?? ff 15", 0, TRUE );
	ADD_SIG( "forceTailState", "0f 84 ?? ?? ?? ?? 85 c0 0f 84 ?? ?? ?? ?? 8d be", 0, TRUE ); // libcocos2d.dll

}

// https://stackoverflow.com/questions/50933649/how-to-get-memory-address-knowing-pointer
UCHAR* MgrGetPointerAddress( UCHAR* Addy, std::vector<unsigned int> offsets )
{
	UCHAR* addr = Addy;
	for ( unsigned int i = 0; i < offsets.size( ); ++i )
	{
		ReadProcessMemory( GetCurrentProcess( ), ( BYTE* )addr, &addr, sizeof( addr ), 0 );
		addr += offsets[ i ];
	}
	return addr;
}

BYTE* MgrPatchAddress ( UCHAR* Addy, BYTE Bytes[], INT Size )
{
	BYTE* Temp = ( BYTE* )malloc( Size );

	DWORD OldProtect;
	VirtualProtect( Addy, Size, PAGE_READWRITE, &OldProtect );

	for ( WORD i = 0; i < Size; ++i )
		Temp[ i ] = Addy[ i ];

	for ( WORD i = 0; i < Size; ++i )
		Addy[ i ] = Bytes[ i ];

	VirtualProtect( Addy, Size, OldProtect, &OldProtect );
		
	return Temp;
}

UCHAR* MgrGetPointerAddressFromPattern( std::string hookName, std::vector<unsigned int> offsets )
{
	UCHAR* addr = MgrGetAddress( hookName, 0 );
	for ( unsigned int i = 0; i < offsets.size( ); ++i )
	{
		ReadProcessMemory( GetCurrentProcess( ), ( BYTE* )addr, &addr, sizeof( addr ), 0 );
		addr += offsets[ i ];
	}
	return addr;
}

UCHAR* MgrGetAddress( std::string hookName, const char* ModuleName )
{
	for ( unsigned int i = 0; i < SignatureList.size( ); ++i )
	{
		if ( hookName == SignatureName[ i ] )
		{
			UCHAR* Patterned = PatternScan( GetModuleHandleA( ModuleName ), SignatureList[ i ].c_str( ),
								SignatureOffset[ i ] );

			if ( isDirectFunction[ i ] )
			{
				return Patterned;
			}
			else
			{
				uint32_t Addy = *reinterpret_cast< uint32_t* >( Patterned );
				return ( UCHAR* )Addy;
			}
		}
				
	}
	MessageBoxA( 0, "Signature Couldn't be found!", "", 0 );
	return NULL;
}
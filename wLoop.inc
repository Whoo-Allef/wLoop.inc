/*
	****	Include responsavel por passar apenas em playerids conectados.	***
					https://forum.sa-mp.com/member.php?u=309762
	Exemplo de Uso:
		wLoop(i) {
			SendClientMessage(i, -1, "Usando o loop");
		}
*/

#define wLoop(%0) for(new %0; %0 < sizeof(playerConnected_ID); %0++) if(playerConnected_ID[%0] == INVALID_PLAYER_ID) break;


// variavel para armazenar os ids conectados.
new playerConnected_ID[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...};


public OnPlayerConnect(playerid) 
{
	// insert playerid
	LoopInsertID(playerid);

    #if defined LoopOnPlayerConnect
        return LoopOnPlayerConnect(playerid);
    #else
		return 1;
	#endif
}

public OnPlayerDisconnect(playerid, reason) 
{
	// Remove playerid
	LoopRemoveID(playerid);

	#if defined Loop_OnPlayerDisconnect
		return Loop_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

// Remove IDS.
LoopRemoveID(playerid) 
{
	for(new a; a < sizeof(playerConnected_ID); a++) 
	{
		if(playerConnected_ID[a] == playerid) 
		{
			playerConnected_ID[a] = INVALID_PLAYER_ID;
			LoopUpdateIDs();
			break;
		}
	}
	return 1;
}

// Insert IDS.
LoopInsertID(playerid) 
{
	for(new a; a < sizeof(playerConnected_ID); a++)
	{
		if(playerConnected_ID[a] == INVALID_PLAYER_ID)
		{
			playerConnected_ID[a] = playerid;
			break;
		}
	}
	return 1;
}

// Update IDS.
LoopUpdateIDs() 
{
	for(new a; a < sizeof(playerConnected_ID); a++)
	{
		if(playerConnected_ID[a] != INVALID_PLAYER_ID) continue;

		if(playerConnected_ID[a + 1] != INVALID_PLAYER_ID)
		{
			playerConnected_ID[a] = playerConnected_ID[a + 1];
			playerConnected_ID[a + 1] = INVALID_PLAYER_ID;
			continue;
		}
		break;
	}
	return 1;
}

// Hook OnPlayerDisconnect
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect LoopOnPlayerDisconnect

#if defined LoopOnPlayerDisconnect
    forward LoopOnPlayerDisconnect(playerid, reason);
#endif

// Hook OnPlayerConnect
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect LoopOnPlayerConnect

#if defined LoopOnPlayerConnect
    forward LoopOnPlayerConnect(playerid);
#endif
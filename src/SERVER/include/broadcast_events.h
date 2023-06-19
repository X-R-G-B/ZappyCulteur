/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** broadcast_events
*/

#ifndef BROADCAST_EVENTS_H_
    #define BROADCAST_EVENTS_H_

/**
** @brief broadcast event pnw (new player)
** @param zappy
** @param cl
** @return bool
**/
bool cmd_pnw(ntw_t *ntw, ntw_client_t *cl);

/**
** @brief broadcast event pex (player expulse)
** @param ntw
** @param cl
** @return bool
**/
bool cmd_pex(ntw_t *ntw, ntw_client_t *cl, trantorien_t *tr);

/**
** @brief broadcast event pbc (player broadcast)
** @param ntw
** @param cl
** @param action
** @return bool
**/
bool cmd_pbc(ntw_t *ntw, ntw_client_t *cl, action_t *action);

/**
** @brief broadcast event pfk (player fork)
** @param ntw
** @param cl
** @return bool
**/
bool cmd_pfk(ntw_t *ntw, ntw_client_t *cl);

/**
** @brief broadcast event pdr (player drop ressource)
** @param ntw
** @param cl
** @param action
** @return bool
**/
bool cmd_pdr(ntw_t *ntw, ntw_client_t *cl, action_t *action);

/**
 * @brief broadcast event pgt (player take ressource)
 * @param ntw
 * @param cl
 * @param action
 * @return
 */
bool cmd_pgt(ntw_t *ntw, ntw_client_t *cl, action_t *action);

/**
** @brief broadcast event pdi (player died)
** @param ntw
** @param cl
** @return
**/
bool cmd_pdi(ntw_t *ntw, ntw_client_t *cl);

/**
** @brief broadcast event enw (new egg)
** @param ntw
** @param tr (trantorien)
** @param parent (parent trantorien)
** @return bool
**/
bool cmd_enw(ntw_t *ntw, trantorien_t *tr, trantorien_t *parent);

/**
** @brief broadcast event eht (egg hatched)
** @param ntw
** @param cl
** @return
**/
bool cmd_ebo(ntw_t *ntw, ntw_client_t *cl);

/**
** @brief broadcast event edi (egg died)
** @param ntw
** @param cl
** @return
**/
bool cmd_edi(ntw_t *ntw, ntw_client_t *cl);

/**
** @brief broadcast event smg (server message)
** @param ntw
** @param smg
** @return
**/
bool cmd_smg(ntw_t *ntw, const char *smg);

/**
** @brief broadcast event seg (end game)
** @param ntw
** @param cl
** @return
**/
bool cmd_seg(ntw_t *ntw, client_t *cl);

/**
** @brief broadcast event suc (success)
** @param cl
** @return
**/
bool cmd_suc(ntw_client_t *cl);

/**
** @brief broadcast event sbp (error)
** @param cl
** @return
**/
bool cmd_sbp(ntw_client_t *cl);

#endif // BROADCAST_EVENTS_H_

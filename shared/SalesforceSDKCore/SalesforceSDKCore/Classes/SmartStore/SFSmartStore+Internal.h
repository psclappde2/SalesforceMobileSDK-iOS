/*
 Copyright (c) 2012, salesforce.com, inc. All rights reserved.
 
 Redistribution and use of this software in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions
 and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of
 conditions and the following disclaimer in the documentation and/or other materials provided
 with the distribution.
 * Neither the name of salesforce.com, inc. nor the names of its contributors may be used to
 endorse or promote products derived from this software without specific prior written
 permission of salesforce.com, inc.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
#import "SFSmartStore.h"
#import "SFUserAccount.h"
#import "SFSmartStoreDatabaseManager.h"

@class FMDatabase;
@class FMResultSet;

@interface SFSmartStore ()

@property (nonatomic, strong) FMDatabaseQueue *storeQueue;
@property (nonatomic, strong) SFUserAccount *user;
@property (nonatomic, strong) SFSmartStoreDatabaseManager *dbMgr;

- (id)initWithName:(NSString*)name user:(SFUserAccount *)user;

/**
 Simply open the db file.
 @return YES if we were able to open the DB file.
 */
- (BOOL)openStoreDatabase;

/**
 @param db This method is expected to be called from [fmdbqueue inDatabase:^(){ ... }]
 @return The soup table name from SOUP_NAMES_TABLE, based on soup name.
 */
- (NSString *)tableNameForSoup:(NSString*)soupName withDb:(FMDatabase*) db;

/**
 Helper method to insert values into an arbitrary table.
 @param tableName The table to insert the data into.
 @param map A dictionary of key-value pairs to be inserted into table.
 @param db This method is expected to be called from [fmdbqueue inDatabase:^(){ ... }]
 @return YES if the insert was successful, NO otherwise.
 */
- (BOOL)insertIntoTable:(NSString *)tableName values:(NSDictionary *)map withDb:(FMDatabase*)db;

/**
 Helper method to update existing values in a table.
 @param tableName The name of the table to update.
 @param values The column name/value mapping to update.
 @param entryId The ID column used to determine what to update.
 @param db This method is expected to be called from [fmdbqueue inDatabase:^(){ ... }]
 @return YES if the update was successful, NO otherwise.
 */
- (BOOL)updateTable:(NSString*)tableName values:(NSDictionary*)map entryId:(NSNumber *)entryId withDb:(FMDatabase*)db;

/**
 @param db This method is expected to be called from [fmdbqueue inDatabase:^(){ ... }]
 @return The map of an indexSpec path to a column name from SOUP_INDEX_MAP_TABLE.
 */
- (NSString *)columnNameForPath:(NSString *)path inSoup:(NSString *)soupName withDb:(FMDatabase*)db;

/**
 @return The key used to encrypt the store.
 */
+ (NSString *)encKey;

/**
 FOR UNIT TESTING.  Removes all of the shared smart store objects from memory (persisted stores remain).
 */
+ (void)clearSharedStoreMemoryState;

/**
 Convert smart sql to sql.
 @param smartSql The smart sql to convert.
 @return The sql.
 */
- (NSString*) convertSmartSql:(NSString*)smartSql;

@end

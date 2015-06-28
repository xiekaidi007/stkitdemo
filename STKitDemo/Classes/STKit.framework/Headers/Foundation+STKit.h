//
//  Foundation+STKit.h
//  STKit
//
//  Created by SunJiangting on 13-10-5.
//  Copyright (c) 2013年 SunJiangting. All rights reserved.
//

#import <STKit/STDefines.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/// 是否是某个类的子类
ST_EXTERN BOOL STClassIsKindOfClass(Class _class, Class parentClass);
/// 根据基本类型+值，转换成NSValue， 不包含CGRect等等
ST_EXTERN NSValue *STCreateValueFromPrimitivePointer(void *pointer, const char *objCType);
/// 某个类是否响应某个类方法
ST_EXTERN BOOL STClassRespondsToSelector(Class class, SEL aSelector);

ST_EXTERN void STPrintClassMethods(Class cls);
ST_EXTERN void STPrintClassProperities(Class cls);

#pragma mark - STRadian Degree
ST_EXTERN CGFloat STRadianToDegree(CGFloat radian);

ST_EXTERN CGFloat STDegreeToRadian(CGFloat degree);

ST_EXTERN NSString *STTemporaryDirectory();
ST_EXTERN NSString *STDocumentDirectory();
ST_EXTERN NSString *STLibiaryDirectory();
ST_EXTERN NSString *STCacheDirectory();

#pragma mark - BitOffset
ST_EXTERN BOOL STGetBitOffset(NSInteger value, NSInteger offset);

ST_EXTERN NSInteger STSetBitOffset(NSInteger value, NSInteger bit, BOOL t);

ST_EXTERN NSInteger STCleanBitOffset(NSInteger value, NSInteger bit);

@interface NSObject (STKit)
/**
 * @brief 给全局变量赋值/读取
 *
 * @param value  全局变量的新值
 * @param varName  全局变量名称.PS:属性的话记得加下划线 _property
 *
 * @discussion 如果是基本类型的var的话需要将value转换成 void *
 *
 */
- (void)setValue:(id)value forVar:(NSString *)varName;
- (id)valueForVar:(NSString *)varName;
/**
 * @brief 该类是否响应某个selector的类方法
 *
 * @param aSelector 类方法名称。
 *
 * @attention 不要和对象的respondsToSelector:搞混了，这个是对于某个Class的
 */
+ (BOOL)classRespondsToSelector:(SEL)aSelector;
@end

@interface NSObject (STPerformSelector)
/// 注明： 如果返回值为基本类型，struct除外，其余都转换为NSNumber。 如果返回值是struct。则转为NSValue,
/// 如果selector不存在，则直接返回nil, 如果参数不足，则nil填充
- (id)performSelector:(SEL)aSelector withObjects:(id)object, ... __attribute__((sentinel(0, 1)));
- (id)st_performSelector:(SEL)aSelector withObjects:(id)object, ... __attribute__((sentinel(0, 1)));

@end

@interface NSString (STKit)
/// 是否包含子字符串
- (BOOL)contains:(NSString *)substring;
/// 过滤空格
- (NSString *)stringByTrimingWhitespace;
/// substring的range
- (NSArray *)rangesOfString:(NSString *)string;
/// 使用正则表达式将字符串分割，array中不包含正则表达式
- (NSArray *)componentsSeparatedByRegex:(NSString *)regex;
/// ranges substring's range
- (NSArray *)componentsSeparatedByRegex:(NSString *)regex ranges:(NSArray **)ranges;
/// ranges 表示正则表达式的区间。 里面为字符串，使用 NSRangeFromString可以直接解析
- (NSArray *)componentsSeparatedByRegex:(NSString *)regex regexRanges:(NSArray **)ranges;
- (NSArray *)componentsSeparatedByRegex:(NSString *)regex ranges:(NSArray **)ranges checkingResults:(NSArray **)checkingResults;
- (NSString *)stringByAddingHTMLEscapes;
- (NSString *)stringByReplacingHTMLEscapes;
- (NSData *)UTF8EncodedData;
/// md5 加密
- (NSString *)md5String;
- (NSString *)sha1String;

@end

@interface NSData (STKit)

+ (NSData *)dataWithBase64EncodedString:(NSString *)base64String;

- (NSString *)base64String;

- (NSString *)UTF8String;

- (NSString *)md5String;

@end

typedef enum STBookSeekDirection {
    STBookSeekDirectionForward = 1,
    STBookSeekDirectionReverse = 2,
} STBookSeekDirection;

/// @require <CoreText/CoreText.h>
@interface NSString (STPagination)

- (NSString *)reverseString;

- (NSString *)substringWithSeekOffset:(NSUInteger)offset
                    constrainedToSize:(CGSize)size
                            direction:(STBookSeekDirection)direction
                           attributes:(NSDictionary *)attributes;
/**
 * @abstract 根据指定的大小,对字符串进行分页,计算出每页显示的字符串区间(NSRange)
 *
 * @param    attributes
 *分页所需的字符串样式,需要指定字体大小,行间距等。iOS6.0以上请参见UIKit中NSAttributedString的扩展,iOS6.0以下请参考CoreText中的CTStringAttributes.h
 * @param    size        需要参考的size。即在size区域内
 */
- (NSArray *)paginationWithAttributes:(NSDictionary *)attributes constrainedToSize:(CGSize)size;

@end

@class UIFont;
@interface NSString (STDrawSize)

- (CGFloat)heightWithFont:(UIFont *)font constrainedToWidth:(CGFloat)size;

@end

#pragma mark - NSNotificationOnMainThread
@interface NSNotificationCenter (STPostOnMainThread)

- (void)postNotificationOnMainThread:(NSString *)aName;
- (void)postNotificationOnMainThreadWithName:(NSString *)aName object:(id)anObject;
- (void)postNotificationOnMainThreadWithName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

@end

/**
 * @abstract timer fired时候的回调
 *
 * @param    timer 所创建的timer
 * @param    invalidate  是否invalidate当前的timer
 */
typedef void(^STTimerFiredHandler) (NSTimer * timer, BOOL *invalidate);
/// 使用block的形式，简化timer的使用
@interface NSTimer (STBlock)
+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)timeInterval firedHandler:(STTimerFiredHandler)handler;
+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)timeInterval firedHandler:(STTimerFiredHandler)handler;
- (instancetype)initWithFireDate:(NSDate *)date interval:(NSTimeInterval)interval  firedHandler:(STTimerFiredHandler)handler;

@end


#pragma mark - NSDateComponents
@interface NSDate (STKit)

@property(readonly) NSInteger year;
@property(readonly) NSInteger month;
@property(readonly) NSInteger day;

@property(readonly) NSInteger hour;
@property(readonly) NSInteger minute;
@property(readonly) NSInteger second;

@property(readonly) NSDateComponents *components;

/// MS MillSecond
+ (NSDate *)dateWithMSTimeIntervalSince1970:(NSTimeInterval)millisecond;

+ (NSString *)dateWithTimeIntervalSince1970:(NSTimeInterval)millisecond format:(NSString *)format;

+ (NSString *)dateWithMSTimeIntervalSince1970:(NSTimeInterval)millisecond format:(NSString *)format;
+ (NSString *)timestampFormattedStringWithTimeIntervalSince1970:(NSTimeInterval)millisecond;

- (NSString*)timestampFormattedString;

@end

#pragma mark - STJSON

@interface NSData (STKitJSON)

- (id)JSONValue;

@end

@interface NSString (STKitJSON)

- (id)JSONValue;

@end

@interface NSDictionary (STKitJSON)

+ (id)dictionaryWithJSONString:(NSString *)JSONString;
+ (id)dictionaryWithJSONData:(NSData *)JSONData;
- (NSString *)JSONString;

@end

@interface NSArray (STKitJSON)

+ (id)arrayWithJSONString:(NSString *)JSONString;
+ (id)arrayWithJSONData:(NSData *)JSONData;
- (NSString *)JSONString;

@end

#pragma mark - STSecureAccessor

@interface NSArray (STSecure)

- (id)st_objectAtIndex:(NSUInteger)index;

@end

@interface NSDictionary (STSecure)

- (NSInteger)st_integerValueForKey:(NSString *)key;
- (long long)st_longLongValueForKey:(NSString *)key;
- (int)st_intValueForKey:(NSString *)key;
- (double)st_doubleValueForKey:(NSString *)key;
- (BOOL)st_boolValueForKey:(NSString *)key;

- (NSArray *)st_arrayValueForKey:(NSString *)key;
- (NSDictionary *)st_dictionaryValueForKey:(NSString *)key;
- (NSString *)st_stringValueForKey:(NSString *)key;

@end

@interface NSArray (STClass)

- (BOOL)containsClass:(Class) class;
- (NSUInteger)indexOfClass:(Class) class;
- (NSUInteger)firstIndexOfClass:(Class) class;
- (NSUInteger)lastIndexOfClass:(Class) class;

- (id)firstObjectOfClass:(Class) class;
- (id)lastObjectOfClass:(Class) class;

@end

@interface NSDictionary (STURLQuery)
/// connector is between key and value, separator are between each record
/// eg. @{@"name":@"suen", @"age":@(24)} will be convert to name=suen&age=24 (connector=,separator&)
- (NSString *)st_compontentsJoinedByConnector:(NSString *)connector separator:(NSString *)separator;
/// URL
- (NSString *)st_compontentsJoinedUsingURLStyle;

+ (instancetype)dictionaryWithURLQuery:(NSString *)URLQuery;

@end

@interface NSString (STNetwork)
- (NSString *)st_stringByURLEncoded;
- (NSString *)st_stringByURLDecoded;
@end

extern NSString *STKitGetVersion(void);
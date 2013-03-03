/* rbSFML
 * Copyright (c) 2012 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#define AUDIO_SOUNDBUFFER_CPP

#include "SoundBuffer.hpp"
#include <System/SFML.hpp>
#include <System/Time.hpp>
#include <System/NonCopyable.hpp>

void rbSoundBuffer::Init( VALUE SFML )
{
    rbSoundBuffer::Class = rb_define_class_under( SFML, "SoundBuffer", rb_cObject );

    // Class methods
    rb_define_alloc_func( rbSoundBuffer::Class, rbMacros::Allocate< sf::SoundBuffer > );

    // Instance methods
    ext_define_method( rbSoundBuffer::Class, "initialize_copy",   rbSoundBuffer::InitializeCopy,   1 );
    ext_define_method( rbSoundBuffer::Class, "marshal_dump",      rbSoundBuffer::MarshalDump,      0 );
    ext_define_method( rbSoundBuffer::Class, "marshal_load",      rbSoundBuffer::MarshalLoad,      1 );
    ext_define_method( rbSoundBuffer::Class, "load_from_file",    rbSoundBuffer::LoadFromFile,     1 );
    ext_define_method( rbSoundBuffer::Class, "load_from_memory",  rbSoundBuffer::LoadFromMemory,   1 );
    ext_define_method( rbSoundBuffer::Class, "load_from_stream",  rbSoundBuffer::LoadFromStream,   1 );
    ext_define_method( rbSoundBuffer::Class, "load_from_samples", rbSoundBuffer::LoadFromSamples, -1 );
    ext_define_method( rbSoundBuffer::Class, "save_to_file",      rbSoundBuffer::SaveToFile,       1 );
    ext_define_method( rbSoundBuffer::Class, "samples",           rbSoundBuffer::GetSamples,       0 );
    ext_define_method( rbSoundBuffer::Class, "sample_count",      rbSoundBuffer::GetSampleCount,   0 );
    ext_define_method( rbSoundBuffer::Class, "sample_rate",       rbSoundBuffer::GetSampleRate,    0 );
    ext_define_method( rbSoundBuffer::Class, "channel_count",     rbSoundBuffer::GetChannelCount,  0 );
    ext_define_method( rbSoundBuffer::Class, "duration",          rbSoundBuffer::GetDuration,      0 );
    ext_define_method( rbSoundBuffer::Class, "==",                rbSoundBuffer::Equal,            1 );
    ext_define_method( rbSoundBuffer::Class, "inspect",           rbSoundBuffer::Inspect,          0 );

    // Instance aliasses
    rb_define_alias( rbSoundBuffer::Class, "loadFromFile",      "load_from_file"    );
    rb_define_alias( rbSoundBuffer::Class, "load_file",         "load_from_file"    );
    rb_define_alias( rbSoundBuffer::Class, "load",              "load_from_file"    );
    rb_define_alias( rbSoundBuffer::Class, "loadFromMemory",    "load_from_memory"  );
    rb_define_alias( rbSoundBuffer::Class, "load_memory",       "load_from_memory"  );
    rb_define_alias( rbSoundBuffer::Class, "loadFromStream",    "load_from_stream"  );
    rb_define_alias( rbSoundBuffer::Class, "load_stream",       "load_from_stream"  );
    rb_define_alias( rbSoundBuffer::Class, "loadFromSamples",   "load_from_samples" );
    rb_define_alias( rbSoundBuffer::Class, "load_samples",      "load_from_samples" );
    rb_define_alias( rbSoundBuffer::Class, "saveToFile",        "save_to_file"      );
    rb_define_alias( rbSoundBuffer::Class, "save_file",         "save_to_file"      );
    rb_define_alias( rbSoundBuffer::Class, "save",              "save_to_file"      );
    rb_define_alias( rbSoundBuffer::Class, "getSamples",        "samples"           );
	rb_define_alias( rbSoundBuffer::Class, "get_samples",       "samples"           );
    rb_define_alias( rbSoundBuffer::Class, "getSampleCount",    "sample_count"      );
	rb_define_alias( rbSoundBuffer::Class, "get_sample_count",  "sample_count"      );
    rb_define_alias( rbSoundBuffer::Class, "getSampleRate",     "sample_rate"       );
	rb_define_alias( rbSoundBuffer::Class, "get_sample_rate",   "sample_rate"       );
    rb_define_alias( rbSoundBuffer::Class, "getChannelCount",   "channel_count"     );
	rb_define_alias( rbSoundBuffer::Class, "get_channel_count", "channel_count"     );
    rb_define_alias( rbSoundBuffer::Class, "getDuration",       "duration"          );
	rb_define_alias( rbSoundBuffer::Class, "get_duration",      "duration"          );
    rb_define_alias( rbSoundBuffer::Class, "to_s",              "inspect"           );
}

// SoundBuffer#initialize_copy( sound_buffer )
VALUE rbSoundBuffer::InitializeCopy( VALUE aSelf, VALUE aSource )
{
    *rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class ) = *rbMacros::ToSFML< sf::SoundBuffer >( aSource, rbSoundBuffer::Class );
    return aSelf;
}

// SoundBuffer#marshal_dump
VALUE rbSoundBuffer::MarshalDump( VALUE aSelf )
{
    sf::SoundBuffer* soundBuffer = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class );

    VALUE ptr[ 3 ];
    ptr[ 0 ] = rb_str_new( ( const char* ) soundBuffer->getSamples(),
							soundBuffer->getSampleCount() * 2 );
    ptr[ 1 ] = UINT2NUM( soundBuffer->getChannelCount() );
    ptr[ 2 ] = UINT2NUM( soundBuffer->getSampleRate() );
    return rb_ary_new4( 3, ptr );
}

// SoundBuffer#marshal_load
VALUE rbSoundBuffer::MarshalLoad( VALUE aSelf, VALUE aData )
{
    sf::SoundBuffer* soundBuffer = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class );

    VALUE* ptr = RARRAY_PTR( aData );
    const sf::Int16* samples    = ( const sf::Int16* )RSTRING_PTR( ptr[ 0 ] );
    std::size_t sampleCount   = RSTRING_LEN( ptr[ 0 ] ) / 2;
    unsigned int channelCount = NUM2UINT( ptr[ 1 ] );
    unsigned int sampleRate    = NUM2UINT( ptr[ 2 ] );

    soundBuffer->loadFromSamples( samples, sampleCount, channelCount,
                                   sampleRate );
    return Qnil;
}

// SoundBuffer#load_from_file(filename)
// SoundBuffer#loadFromFile(filename)
// SoundBuffer#load_file(filename)
// SoundBuffer#load(filename)
VALUE rbSoundBuffer::LoadFromFile( VALUE aSelf, VALUE aFilename )
{
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->loadFromFile( StringValueCStr( aFilename ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#load_from_memory(data)
// SoundBuffer#loadFromMemory(data)
// SoundBuffer#load_memory(data)
VALUE rbSoundBuffer::LoadFromMemory( VALUE aSelf, VALUE aData )
{
    StringValue( aData );
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->loadFromMemory( RSTRING_PTR( aData ),
																								   RSTRING_LEN( aData ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#load_from_stream(stream)
// SoundBuffer#loadFromStream(stream)
// SoundBuffer#load_stream(stream)
VALUE rbSoundBuffer::LoadFromStream( VALUE aSelf, VALUE aStream )
{
    rbInputStream stream( aStream );
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->loadFromStream( stream );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#load_from_samples(samples, channels_count, sample_rate)
// SoundBuffer#loadFromSamples(samples, channels_count, sample_rate)
// SoundBuffer#load_samples(samples, channels_count, sample_rate)
// SoundBuffer#load_from_samples(samples, samples_count, channels_count, sample_rate)
// SoundBuffer#loadFromSamples(samples, samples_count, channels_count, sample_rate)
// SoundBuffer#load_samples(samples, samples_count, channels_count, sample_rate)
VALUE rbSoundBuffer::LoadFromSamples( int argc, VALUE argv[], VALUE aSelf )
{
    unsigned int channelCount;
    unsigned int sampleRate;
    switch( argc )
    {
        case 3:
            channelCount = NUM2UINT( argv[ 1 ] );
            sampleRate = NUM2UINT( argv[ 2 ] );
            break;
        case 4:
            channelCount = NUM2UINT( argv[ 2 ] );
            sampleRate = NUM2UINT( argv[ 3 ] );
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 3..4)", argc );
    }
    VALUE samplesAry = rb_ary_to_ary( argv[ 0 ] );
    std::size_t sampleCount = RARRAY_LEN( samplesAry );
    VALUE* samplesPtr = RARRAY_PTR( samplesAry );
    if( argc == 4 and sampleCount != NUM2UINT( argv[ 1 ] ) )
    {
        rb_raise( rb_eArgError, "expected array size to be %lu", sampleCount );
    }
    sf::Int16* samples = new sf::Int16[ sampleCount ];
    for( std::size_t index = 0; index < sampleCount; index++ )
    {
        samples[ index ] = NUM2INT( samplesPtr[ index ] );
    }
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->loadFromSamples( samples, sampleCount,
																			channelCount, sampleRate );
    delete[] samples;
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#save_to_file(filename)
// SoundBuffer#SaveToFile(filename)
// SoundBuffer#save_file(filename)
// SoundBuffer#save(filename)
VALUE rbSoundBuffer::SaveToFile( VALUE aSelf, VALUE aFilename )
{
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->saveToFile( StringValueCStr( aFilename ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#samples
// SoundBuffer#get_samples
// SoundBuffer#getSamples
VALUE rbSoundBuffer::GetSamples( VALUE aSelf )
{
    const sf::Int16* samples  = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getSamples();
    std::size_t sampleCount = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getSampleCount();
    VALUE ary = rb_ary_new2( sampleCount );
    for( std::size_t index = 0; index < sampleCount; index++ )
    {
        rb_ary_push( ary, INT2FIX( samples[ index ] ) );
    }

    return ary;
}

// SoundBuffer#sample_count
// SoundBuffer#get_sample_count
// SoundBuffer#getSampleCount
VALUE rbSoundBuffer::GetSampleCount( VALUE aSelf )
{
    return INT2NUM( rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getSampleCount() );
}

// SoundBuffer#sample_rate
// SoundBuffer#get_sample_rate
// SoundBuffer#getSampleRate
VALUE rbSoundBuffer::GetSampleRate( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getSampleRate() );
}

// SoundBuffer#channel_count
// SoundBuffer#get_channel_count
// SoundBuffer#getChannelCount
VALUE rbSoundBuffer::GetChannelCount( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getChannelCount() );
}

// SoundBuffer#duration
// SoundBuffer#get_duration
// SoundBuffer#getDuration
VALUE rbSoundBuffer::GetDuration( VALUE aSelf )
{
	sf::Time *time = rbMacros::Allocate< sf::Time >();
	*time = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getDuration();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// SoundBuffer#==(other)
VALUE rbSoundBuffer::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbSoundBuffer::Class ) ) return Qfalse;
    sf::SoundBuffer* left = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class );
    sf::SoundBuffer* right = rbMacros::ToSFML< sf::SoundBuffer >( anOther, rbSoundBuffer::Class );

    if( left->getSampleCount() != right->getSampleCount() ) return Qfalse;
    if( left->getSampleRate() != right->getSampleRate() ) return Qfalse;
    if( left->getChannelCount() != right->getChannelCount() ) return Qfalse;

    std::size_t sampleCount = left->getSampleCount();
    const sf::Int16* leftSamples = left->getSamples();
    const sf::Int16* rightSamples = right->getSamples();
    for( std::size_t index = 0; index < sampleCount; index++ )
    {
        if( leftSamples[ index ] != rightSamples[ index ] ) return Qfalse;
    }

    return Qtrue;
}

// SoundBuffer#inspect
// SoundBuffer#to_s
VALUE rbSoundBuffer::Inspect( VALUE aSelf )
{
    return rb_sprintf("%s(%p: %ims)",
                      rb_obj_classname( aSelf ),
                      (void*)aSelf,
                      rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->getDuration().asMilliseconds() );
}

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
#include "Time.hpp"

void rbSoundBuffer::Init( VALUE SFML )
{
    rbSoundBuffer::Class = rb_define_class_under( SFML, "SoundBuffer", rb_cObject );

    // Class methods
    rb_define_alloc_func( rbSoundBuffer::Class, rbMacros::Allocate< sf::SoundBuffer > );

    // Instance methods
    rb_define_method( rbSoundBuffer::Class, "initialize_copy",   rbSoundBuffer::InitializeCopy,   1 );
    rb_define_method( rbSoundBuffer::Class, "marshal_dump",      rbSoundBuffer::MarshalDump,      0 );
    rb_define_method( rbSoundBuffer::Class, "marshal_load",      rbSoundBuffer::MarshalLoad,      1 );
    rb_define_method( rbSoundBuffer::Class, "load_from_file",    rbSoundBuffer::LoadFromFile,     1 );
    rb_define_method( rbSoundBuffer::Class, "load_from_memory",  rbSoundBuffer::LoadFromMemory,   1 );
    rb_define_method( rbSoundBuffer::Class, "load_from_stream",  rbSoundBuffer::LoadFromStream,   1 );
    rb_define_method( rbSoundBuffer::Class, "load_from_samples", rbSoundBuffer::LoadFromSamples, -1 );
    rb_define_method( rbSoundBuffer::Class, "save_to_file",      rbSoundBuffer::SaveToFile,       1 );
    rb_define_method( rbSoundBuffer::Class, "samples",           rbSoundBuffer::GetSamples,       0 );
    rb_define_method( rbSoundBuffer::Class, "sample_count",      rbSoundBuffer::GetSampleCount,   0 );
    rb_define_method( rbSoundBuffer::Class, "sample_rate",       rbSoundBuffer::GetSampleRate,    0 );
    rb_define_method( rbSoundBuffer::Class, "channel_count",     rbSoundBuffer::GetChannelCount,  0 );
    rb_define_method( rbSoundBuffer::Class, "duration",          rbSoundBuffer::GetDuration,      0 );
    rb_define_method( rbSoundBuffer::Class, "==",                rbSoundBuffer::Equal,            1 );
    rb_define_method( rbSoundBuffer::Class, "inspect",           rbSoundBuffer::Inspect,          0 );
    rb_define_method( rbSoundBuffer::Class, "memory_usage",      rbSoundBuffer::GetMemoryUsage,   0 );

    // Instance aliasses
    rb_define_alias( rbSoundBuffer::Class, "LoadFromFile",     "load_from_file"    );
    rb_define_alias( rbSoundBuffer::Class, "load_file",        "load_from_file"    );
    rb_define_alias( rbSoundBuffer::Class, "load",             "load_from_file"    );
    rb_define_alias( rbSoundBuffer::Class, "LoadFromMemory",   "load_from_memory"  );
    rb_define_alias( rbSoundBuffer::Class, "load_memory",      "load_from_memory"  );
    rb_define_alias( rbSoundBuffer::Class, "LoadFromStream",   "load_from_stream"  );
    rb_define_alias( rbSoundBuffer::Class, "load_stream",      "load_from_stream"  );
    rb_define_alias( rbSoundBuffer::Class, "LoadFromSamples",  "load_from_samples" );
    rb_define_alias( rbSoundBuffer::Class, "load_samples",     "load_from_samples" );
    rb_define_alias( rbSoundBuffer::Class, "SaveToFile",       "save_to_file"      );
    rb_define_alias( rbSoundBuffer::Class, "save_file",        "save_to_file"      );
    rb_define_alias( rbSoundBuffer::Class, "save",             "save_to_file"      );
    rb_define_alias( rbSoundBuffer::Class, "GetSamples",       "samples"           );
    rb_define_alias( rbSoundBuffer::Class, "GetSampleCount",   "sample_count"      );
    rb_define_alias( rbSoundBuffer::Class, "GetSampleRate",    "sample_rate"       );
    rb_define_alias( rbSoundBuffer::Class, "GetChannelCount",  "channel_count"    );
    rb_define_alias( rbSoundBuffer::Class, "GetDuration",      "duration"          );
    rb_define_alias( rbSoundBuffer::Class, "to_s",             "inspect"           );
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
    ptr[ 0 ] = rb_str_new( ( const char* ) soundBuffer->GetSamples(),
							soundBuffer->GetSampleCount() * 2 );
    ptr[ 1 ] = UINT2NUM( soundBuffer->GetChannelCount() );
    ptr[ 2 ] = UINT2NUM( soundBuffer->GetSampleRate() );
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

    soundBuffer->LoadFromSamples( samples, sampleCount, channelCount,
                                   sampleRate );
    return Qnil;
}

// SoundBuffer#load_from_file(filename)
// SoundBuffer#LoadFromFile(filename)
// SoundBuffer#load_file(filename)
// SoundBuffer#load(filename)
VALUE rbSoundBuffer::LoadFromFile( VALUE aSelf, VALUE aFilename )
{
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->LoadFromFile( StringValueCStr( aFilename ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#load_from_memory(data)
// SoundBuffer#LoadFromMemory(data)
// SoundBuffer#load_memory(data)
VALUE rbSoundBuffer::LoadFromMemory( VALUE aSelf, VALUE aData )
{
    StringValue( aData );
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->LoadFromMemory( RSTRING_PTR( aData ),
																								   RSTRING_LEN( aData ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#load_from_stream(stream)
// SoundBuffer#LoadFromStream(stream)
// SoundBuffer#load_stream(stream)
VALUE rbSoundBuffer::LoadFromStream( VALUE aSelf, VALUE aStream )
{
    rbInputStream stream( aStream );
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->LoadFromStream( stream );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#load_from_samples(samples, channels_count, sample_rate)
// SoundBuffer#LoadFromSamples(samples, channels_count, sample_rate)
// SoundBuffer#load_samples(samples, channels_count, sample_rate)
// SoundBuffer#load_from_samples(samples, samples_count, channels_count, sample_rate)
// SoundBuffer#LoadFromSamples(samples, samples_count, channels_count, sample_rate)
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
        rb_raise( rb_eArgError, "expected array size to be %d", sampleCount );
    }
    sf::Int16* samples = new sf::Int16[ sampleCount ];
    for( std::size_t index = 0; index < sampleCount; index++ )
    {
        samples[ index ] = NUM2INT( samplesPtr[ index ] );
    }
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->LoadFromSamples( samples, sampleCount,
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
    bool ret = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->SaveToFile( StringValueCStr( aFilename ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// SoundBuffer#samples
// SoundBuffer#GetSamples
VALUE rbSoundBuffer::GetSamples( VALUE aSelf )
{
    const sf::Int16* samples  = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetSamples();
    std::size_t sampleCount = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetSampleCount();
    VALUE ary = rb_ary_new2( sampleCount );
    for( std::size_t index = 0; index < sampleCount; index++ )
    {
        rb_ary_push( ary, INT2FIX( samples[ index ] ) );
    }

    return ary;
}

// SoundBuffer#samples_count
// SoundBuffer#GetSamplesCount
VALUE rbSoundBuffer::GetSampleCount( VALUE aSelf )
{
    return INT2NUM( rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetSampleCount() );
}

// SoundBuffer#sample_rate
// SoundBuffer#GetSampleRate
VALUE rbSoundBuffer::GetSampleRate( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetSampleRate() );
}

// SoundBuffer#channels_count
// SoundBuffer#GetChannelsCount
VALUE rbSoundBuffer::GetChannelCount( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetChannelCount() );
}

// SoundBuffer#duration
// SoundBuffer#GetDuration
VALUE rbSoundBuffer::GetDuration( VALUE aSelf )
{
	sf::Time *time = rbMacros::Allocate< sf::Time >();
	*time = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetDuration();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// SoundBuffer#==(other)
VALUE rbSoundBuffer::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbSoundBuffer::Class ) ) return Qfalse;
    sf::SoundBuffer* left = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class );
    sf::SoundBuffer* right = rbMacros::ToSFML< sf::SoundBuffer >( anOther, rbSoundBuffer::Class );

    if( left->GetSampleCount() != right->GetSampleCount() ) return Qfalse;
    if( left->GetSampleRate() != right->GetSampleRate() ) return Qfalse;
    if( left->GetChannelCount() != right->GetChannelCount() ) return Qfalse;

    std::size_t sampleCount = left->GetSampleCount();
    const sf::Int16* leftSamples = left->GetSamples();
    const sf::Int16* rightSamples = right->GetSamples();
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
                      rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetDuration() );
}

// SoundBuffer#memory_usage
VALUE rbSoundBuffer::GetMemoryUsage( VALUE aSelf )
{
    std::size_t samplesCount = rbMacros::ToSFML< sf::SoundBuffer >( aSelf, rbSoundBuffer::Class )->GetSampleCount();
    return SIZET2NUM( sizeof( sf::SoundBuffer ) + samplesCount * 2 );
}

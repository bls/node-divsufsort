{
  'targets': [
    {
      'target_name': 'divsufsort',
      'sources': [ 
        'src/divsufsort.cc' 
      ],
      'libraries': [
        '-ldivsufsort',
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
